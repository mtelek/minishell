/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:16:28 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/09 23:28:29 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_pipe_fd(int *pipes, t_main *main)
{
	if (pipe(pipes) == -1)
		error_function(10, main);
}

void	close_child_fds(t_main *main)
{
	int	j;

	j = 0;
	while (j < main->parser->n_pipes)
	{
		close(main->parser->pipes[j][0]);
		close(main->parser->pipes[j][1]);
		j++;
	}
}

int	switching_fds(t_main *main)
{
	int		i;
	__pid_t	pid;

	i = 0;
	while (main->cmd != NULL)
	{
		pid = fork1(main);
		if (pid == 0)
		{
			if (i > 0)
				if (dup2(main->parser->pipes[i - 1][0], STDIN_FILENO) < 0)
					error_function(12, main);
			if (main->cmd->next != NULL)
				if (dup2(main->parser->pipes[i][1], STDOUT_FILENO) < 0)
					error_function(12, main);
			close_child_fds(main);
			// Execute the command directly in the current process
			execvp(main->cmd->cmd, main->cmd->args);
			// execve(main->cmd->cmd, main->cmd->args, main->env);
			perror("execvp");
			exit(1);
		}
		i++;
		main->cmd = main->cmd->next;
	}
	return (i);
}

void	alloc_pipes(t_main *main)
{
	int	i;

	i = 0;
	main->parser->pipes = malloc(sizeof(int *) * main->parser->n_pipes);
	if (!main->parser->pipes)
		error_function(8, main);
	while (i < main->parser->n_pipes)
	{
		main->parser->pipes[i] = malloc(2 * sizeof(int));
		if (!main->parser->pipes[i])
			error_function(9, main);
		set_pipe_fd(main->parser->pipes[i], main);
		i++;
	}
}

void	init_pipes(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc_pipes(main);
	i = switching_fds(main);
	while (j < main->parser->n_pipes)
	{
		close(main->parser->pipes[j][0]);
		close(main->parser->pipes[j][1]);
		j++;
	}
	j = 0;
	while (j++ < i)
		wait(0);
}
