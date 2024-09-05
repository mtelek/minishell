/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:49:08 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 15:16:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	init_heredoc(t_main *main, t_cmd *own_cmd)
{
	int	pipe_fd[2];
	int	j;

	j = 0;
	if (pipe(pipe_fd) == -1)
		pipe_failed(main);
	if (own_cmd->hd_content)
	{
		ft_putstr_fd(own_cmd->hd_content, pipe_fd[1]);
		free(own_cmd->hd_content);
		own_cmd->hd_content = NULL;
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		dup_failed(main, pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	// if (own_cmd->n_heredoc > 1)
	// {
	// 	while (j < own_cmd->n_heredoc)
	// 	{
	// 		free(own_cmd->delimiter[j]);
	// 		j++;
	// 	}
	// 	free(own_cmd->delimiter);
	// 	own_cmd->delimiter = NULL;
	// }
}
