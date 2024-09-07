/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:06:46 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/07 15:28:26 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_pipe_fd(int *pipes, t_main *main)
{
	if (pipe(pipes) == -1)
		pipe_failed(main);
}

int	fork1(t_main *main)
{
	__pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_failed(main);
	else if (pid == 0)
		setup_child_signal_handlers();
	return (pid);
}
