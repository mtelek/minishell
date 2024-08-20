/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:11:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 20:15:55 by mtelek           ###   ########.fr       */
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

char	*no_echo_but_heredoc(char *delimiter, char *content)
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
			free(content);
			content = temp;
		}
		else
			content = ft_strdup(line);
		temp = ft_strjoin(content, "\n");
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
	delimiter = get_txt_name(main, HEREDOC);
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		if (echo_and_heredoc(delimiter))
			return ;
	}
	else
	{
		content = no_echo_but_heredoc(delimiter, content);
		if (content)
		{
			main->hd_content = ft_strdup(content);
			free(content);
		}
	}
}
