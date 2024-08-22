/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:11:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/22 23:35:21 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	find_hd_indicator(t_main *main, t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->hd_indicator == 1)
		{
			get_hd_content(main, cmd);
			break ;
		}
		cmd = cmd->next;
	}
}

int	echo_and_heredoc(char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
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

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (content != NULL)
		{
			temp = ft_strjoin(content, line);
			if (!temp)
				error_function(-1, main); //proper error message needed
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
			error_function(-1, main); //proper error message needed
		free(content);
		content = temp;
		free(line);
	}
	return (content);
}

void	get_hd_content(t_main *main, t_cmd *own_cmd)
{
	char	*content;
	char	*delimiter;

	content = NULL;
	delimiter = ft_strdup(get_txt_name(main, HEREDOC));
	if (!delimiter)
		error_function(-1, main);
	setup_heredoc_signal_handlers();
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		if (echo_and_heredoc(delimiter))
		{
			free(delimiter);
			return ;
		}
	}
	else
	{
		content = no_echo_but_heredoc(delimiter, content, main);
		if (content)
		{
			main->hd_content = ft_strdup(content);
			free(content);
		}
	}
	free(delimiter);
}
