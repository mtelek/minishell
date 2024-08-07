/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:16:28 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/07 23:55:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	fork1(void)
{
	__pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork"); // error function missing
		exit(1);
	}
	return (pid);
}

void	set_pipe_fd(int *pipes)
{
	if (pipe(pipes) == -1)
	{
		perror("pipe"); // error function missing
		exit(1);
	}
}

void	close_child_fds(t_main *main)
{
	int	j;

	j = 0;
	while (j < main->parser->n_pipes) // Close all pipe FDs in child
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
		pid = fork1();
		if (pid == 0) // Child process
		{
			if (i > 0)
				dup2(main->parser->pipes[i - 1][0], STDIN_FILENO);
					// Read from previous pipe
			if (main->cmd->next != NULL)
				dup2(main->parser->pipes[i][1], STDOUT_FILENO);
					// Write to current pipe
			close_child_fds(main);
			execvp(main->cmd->cmd, main->cmd->args);
			//execve(main->cmd->cmd, main->cmd->args, main->env);
			perror("execvp"); // IF execvp fails
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
	main->parser = malloc(sizeof(t_parser));
	if (!main->parser)
		exit(1); // error function missing
	main->parser->n_pipes = count_cmds(main->lexer) - 1;
	main->parser->pipes = malloc(sizeof(int *) * main->parser->n_pipes);
	if (!main->parser->pipes)
		exit(1); // error function missing
	while (i < main->parser->n_pipes)
	{
		main->parser->pipes[i] = malloc(2 * sizeof(int));
		if (!main->parser->pipes[i])
			exit(1); // error function missing
		set_pipe_fd(main->parser->pipes[i]);
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
	while (j < main->parser->n_pipes) // Parent process: Close all pipe FDs
	{
		close(main->parser->pipes[j][0]);
		close(main->parser->pipes[j][1]);
		j++;
	}
	j = 0;
	while (j++ < i) // Wait for all child processes
		wait(0);
}
