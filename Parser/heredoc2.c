/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:11:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/24 00:40:25 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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

int	echo_and_heredoc(char *delimiter, t_main *main)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

char	*no_echo_but_heredoc(char *delimiter, char *content, t_main *main)
{
	char	*line;
	char	*temp;
	char	*count_line;

	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
			{
				main->count_hd_line -= 1;
				count_line = ft_itoa(main->count_line);
				ft_putstrs_fd("bash: warning: here-document at line ",
					count_line, " delimited by end-of-file (wanted `", 2);
				ft_putstrs_fd(delimiter, "')\n", NULL, 2);
				free(count_line);
			}
			free(line);
			break ;
		}
		if (content != NULL)
		{
			temp = ft_strjoin(content, line);
			if (!temp)
				error_function(20, main);
			free(content);
			content = temp;
		}
		else
		{
			content = ft_strdup(line);
			if (!content)
				error_function(-1, main);
		}
		temp = ft_strjoin(content, "\n");
		if (!temp)
			error_function(20, main);
		free(content);
		content = temp;
		free(line);
	}
	main->count_line += main->count_hd_line;
	main->count_hd_line = 0;
	return (content);
}

void	get_hd_content(t_main *main, t_cmd *own_cmd)
{
	char	*content;
	char	*delimiter;

	content = NULL;
	delimiter = get_txt_name(main, HEREDOC, own_cmd->n_heredoc);
	setup_heredoc_signal_handlers();
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		if (echo_and_heredoc(delimiter, main))
			return ;
	}
	else
	{
		content = no_echo_but_heredoc(delimiter, content, main);
		if (content)
			main->hd_content = ft_strdup(content);
	}
	free(content);
}
