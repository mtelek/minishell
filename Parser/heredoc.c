/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:49:08 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 21:53:43 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_heredoc_fd(int *heredoc_fd, t_main *main)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		pipe_failed(main);
	if (main->hd_content)
	{
		ft_putstr_fd(main->hd_content, pipe_fd[1], main);
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
		error_function(11, main);
	while (++i < own_cmd->n_heredoc)
	{
		set_heredoc_fd(&main->parser->heredoc_fd[i], main);
		if (dup2(main->parser->heredoc_fd[i], STDIN_FILENO) < 0)
			dup_failed(main, main->parser->heredoc_fd[i], STDIN_FILENO);
		if (close(main->parser->heredoc_fd[i]) == -1)
			close_failed(main, main->parser->heredoc_fd[i]);
	}
}
