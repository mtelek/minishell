/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:11:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 02:39:16 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char *expand(char *str, t_main *main)
{
    t_expand_node expand_node;
    char *value;
    char *var_name;
    int s_double;
    int e_double;

    expand_node.str = str;
    s_double = qoutes_checker(expand_node.str, 34, -1);
    e_double = qoutes_checker(expand_node.str, 34, s_double);
    if (e_double)
    {
        if (!s_double)
            remove_quotes(expand_node.str, s_double, e_double);
        else if (expand_node.str[0] == 34)
            remove_quotes(expand_node.str, 0, e_double);
        main->quotes_removed = true;
    }
    var_name = find_var_name(expand_node.str, main);
    value = find_env_row(main->env_array, var_name, main);
    if (!value)
    {
        free(var_name);
        return (ft_strdup(str));
    }
    free(expand_node.str);
    expand_node.str = ft_strdup(value);
    free(var_name);
    free(value);
    return (expand_node.str);
}


void	find_hd_indicator(t_main *main, t_cmd *cmd)
{
	t_cmd	*temp_cmd;

	temp_cmd = cmd;
	while (temp_cmd != NULL)
	{
		if (temp_cmd->hd_indicator == 1)
		{
			get_hd_content(main, temp_cmd);
			break ;
		}
		temp_cmd = temp_cmd->next;
	}
}

int	echo_and_heredoc(char **delimiter, t_main *main, t_cmd *own_cmd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter[i]) == 0)
			i++;
		free(line);
		if (i == own_cmd->n_heredoc)
			break ;
	}
	if (i == own_cmd->n_heredoc)
			return (1);
	return (0);
}

char	*no_echo_but_heredoc(char **delimiter, char *content, t_main *main, t_cmd *own_cmd)
{
	char	*line;
	char	*temp;
	char	*count_line;
	int		i;
	char 	*expanded_str;

	i = 0;
	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter[i]) == 0)
		{
			i++;
			if (i == own_cmd->n_heredoc)
				break;
			if (!line)
			{
				main->count_hd_line -= 1;
				count_line = ft_itoa(main->count_line);
				ft_putstrs_fd("bash: warning: here-document at line ",
					count_line, " delimited by end-of-file (wanted `", 2);
				ft_putstrs_fd(delimiter[i], "')\n", NULL, 2);
				free(count_line);
				break;
			}
			continue; 
		}
		if (i == own_cmd->n_heredoc - 1)
		{
			if (content != NULL)
			{
				printf("EXPANDER_DECIDER: %d\n", own_cmd->expander_decider);
				if (own_cmd->expander_decider == true)
					expanded_str = expand(line, main);
				else
					expanded_str = line;
				temp = ft_strjoin(content, expanded_str);
				if (!temp)
					error_function(20, main);
				free(content);
				content = temp;
			}
			else
			{
				if (own_cmd->expander_decider == true)
					expanded_str = expand(line, main);
				else
					expanded_str = line;
				content = ft_strdup(expanded_str);
				if (!content)
					error_function(-1, main);
			}
			temp = ft_strjoin(content, "\n");
			if (!temp)
				error_function(20, main);
			free(content);
			content = temp;
		}
		free(line);
	}
	main->count_line += main->count_hd_line;
	main->count_hd_line = 0;
	return (content);
}

void	get_hd_content(t_main *main, t_cmd *own_cmd)
{
	char	*content;
	int		i;

	i = -1;
	content = NULL;
	own_cmd->delimiter = (char **)malloc(sizeof(char *) * (own_cmd->n_heredoc + 1));
	if (!own_cmd->delimiter)
		error_function(-1, main); //own error fucntion needed
	while (++i < own_cmd->n_heredoc)
		own_cmd->delimiter[i] = get_txt_name(main, HEREDOC, own_cmd->n_heredoc);
	setup_heredoc_signal_handlers();
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		if (echo_and_heredoc(own_cmd->delimiter, main, own_cmd))
			return ;
	}
	else
	{
		content = no_echo_but_heredoc(own_cmd->delimiter, content, main, own_cmd);
		if (content)
		{
			own_cmd->hd_content = ft_strdup(content);
			if (!own_cmd->hd_content)
				error_function(-1, main);
		}
	}
	free(content);
}
