/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:11:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/30 20:48:19 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char 	*expand(char *str, t_main *main)
{
    t_expand_node *expand;
    t_expand_node *current;
	t_lexer lexer;
	
    expand = NULL;
	lexer.str = str;
    cutting_up_lexer_str(&expand, &lexer, main);
    current = expand;
    while (current != NULL)
    {
        current->to_expand = expander_check(current->str);
        if (current->to_expand == true)
            if (expander(current, main) == 1)
				no_var_name_found(current, main);
        current = current->next;
    }
    join_expand_node(expand, main, &lexer);
	return (lexer.str);
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
	char 	*count_line;

	i = 0;
	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter[i]) == 0)
		{
			if (!line)
			{
				main->count_hd_line -= 1;
				count_line = ft_itoa(main->count_line);
				ft_putstrs_fd("bash: warning: here-document at line ",
					count_line, " delimited by end-of-file (wanted `", 2);
				ft_putstrs_fd(delimiter[i], "')\n", NULL, 2);
				free(count_line);
				free(line);
				main->heredoc_flag = 0;
				break;
			}
		}
			i++;
		if (i == own_cmd->n_heredoc)
			break ;
		free(line);
		line = NULL;
	}
	if (i == own_cmd->n_heredoc)
	{
		return (1);
	}
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
			if (!line)
			{
				main->count_hd_line -= 1;
				count_line = ft_itoa(main->count_line);
				ft_putstrs_fd("bash: warning: here-document at line ",
					count_line, " delimited by end-of-file (wanted `", 2);
				ft_putstrs_fd(delimiter[i], "')\n", NULL, 2);
				free(count_line);
				free(line);
				main->heredoc_flag = 0;
				break;
			}
			if (i == own_cmd->n_heredoc)
				break;
			continue; 
		}
		if (i == own_cmd->n_heredoc - 1)
		{
			if (content != NULL)
			{
				if (own_cmd->expander_decider == true)
					expanded_str = expand(line, main);
				else
					expanded_str = line;
				temp = ft_strjoin(content, expanded_str);
				if (!temp)
					error_function(20, main);
				free(content);
				free(expanded_str);
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
				free(expanded_str);
			}
			temp = ft_strjoin(content, "\n");
			if (!temp)
				error_function(20, main);
			free(content);
			content = temp;
		}
	}
	free(line);
	main->count_line += main->count_hd_line;
	main->count_hd_line = 0;
	return (content);
}

void delimiter_check(char *delimiter, t_cmd *own_cmd)
{
	int len;

	if (delimiter)
	{
		len = ft_strlen(delimiter);
		if (len > 1 && delimiter[0] == 39 && delimiter[len - 1] == 39)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[0] == 34 && delimiter[len - 1] == 34)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[0] == 39 && delimiter[1] == 39)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[0] == 34 && delimiter[1] == 34)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[len - 2] == 39 && delimiter[len - 1] == 39)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[len - 2] == 34 && delimiter[len - 1] == 34)
			own_cmd->expander_decider = false;
	}
}

void	remove_surrounding_quotes(t_cmd *own_cmd, int i)
{
    int len;
	int j;

    len = ft_strlen(own_cmd->delimiter[i]);
    if (len > 1 && ((own_cmd->delimiter[i][0] == '"' && own_cmd->delimiter[i][1] == '"') ||
                    (own_cmd->delimiter[i][0] == '\'' && own_cmd->delimiter[i][1] == '\'')))
	{
        for (j = 2; j < len; j++)
            own_cmd->delimiter[i][j - 2] = own_cmd->delimiter[i][j];
        len -= 2;
        own_cmd->delimiter[i][len] = '\0';
	}
    else if (len > 1 && ((own_cmd->delimiter[i][len - 2] == '"' && own_cmd->delimiter[i][len - 1] == '"') ||
                    (own_cmd->delimiter[i][len - 2] == '\'' && own_cmd->delimiter[i][len - 1] == '\'')))
	{
        own_cmd->delimiter[i][len - 2] = '\0';
        len -= 2;
	}
    else if (len > 1 && ((own_cmd->delimiter[i][0] == '"' && own_cmd->delimiter[i][len - 1] == '"') ||
                    (own_cmd->delimiter[i][0] == '\'' && own_cmd->delimiter[i][len - 1] == '\'')))
    {
        for (j = 1; j < len - 1; j++)
            own_cmd->delimiter[i][j - 1] = own_cmd->delimiter[i][j];
        own_cmd->delimiter[i][len - 2] = '\0';
    }
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
    {
        own_cmd->delimiter[i] = get_txt_name(main, HEREDOC, own_cmd->n_heredoc);
    	delimiter_check(own_cmd->delimiter[i], own_cmd);
        remove_surrounding_quotes(own_cmd, i);
    }
    own_cmd->delimiter[i] = NULL;
	setup_heredoc_signal_handlers();
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		if (echo_and_heredoc(own_cmd->delimiter, main, own_cmd))
			return ;
	}
	else
	{
		content = NULL;
		content = no_echo_but_heredoc(own_cmd->delimiter, content, main, own_cmd);
		if (content)
		{
			own_cmd->hd_content = content;
			if (!own_cmd->hd_content)
				error_function(-1, main);
		}
	}
}
