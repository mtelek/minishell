/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:49:08 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/19 22:07:46 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

// check for 'delimeter'

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

void	get_hd_content(t_main *main, t_cmd *own_cmd)
{
	char	*line;
	char	*content;
	char	*delimiter;
	char	*temp;

	content = NULL;
	delimiter = get_txt_name(main, HEREDOC);
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	else
	{
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
			{
				content = ft_strdup(line);
			}
			temp = ft_strjoin(content, "\n");
			free(content);
			content = temp;
			free(line);
		}
		if (content)
		{
			main->hd_content = ft_strdup(content);
			free(content);
		}
	}
}

void	set_heredoc_fd(int *heredoc_fd, t_main *main)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		pipe_failed(main);
	if (main->hd_content)
	{
		ft_putstr_fd(main->hd_content, pipe_fd[1]);
		free(main->hd_content);
		main->hd_content = NULL;
	}
	close(pipe_fd[1]);
	*heredoc_fd = pipe_fd[0];
}

void	init_heredoc(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = -1;
	main->parser->heredoc_fd = malloc(own_cmd->n_heredoc * sizeof(int));
	if (!main->parser->heredoc_fd)
		error_function(15, main); // correct error function
	while (++i < own_cmd->n_heredoc)
	{
		set_heredoc_fd(&main->parser->heredoc_fd[i], main);
		if (dup2(main->parser->heredoc_fd[i], STDIN_FILENO) < 0)
			dup_failed(main, main->parser->heredoc_fd[i], STDIN_FILENO);
		if (close(main->parser->heredoc_fd[i]) == -1)
			close_failed(main, main->parser->heredoc_fd[i]);
	}
}
