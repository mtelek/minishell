/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:16:28 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/19 20:17:17 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_pipe_fd(int *pipes, t_main *main)
{
	if (pipe(pipes) == -1)
		pipe_failed(main);
}

void	close_child_fds(t_main *main)
{
	int	j;

	j = 0;
	while (j < main->parser->n_pipes)
	{
		if (close(main->parser->pipes[j][0]) == -1)
			close_failed(main, main->parser->pipes[j][0]);
		if (close(main->parser->pipes[j][1]) == -1)
			close_failed(main, main->parser->pipes[j][1]);
		j++;
	}
}

t_cmd	*switching_fds(t_main *main)
{
	int		i;
	int		j;
	t_cmd	*current;

	i = 0;
	j = 0;
	current = main->cmd;
	while (current != NULL)
	{
		if (j < main->exec->n_childs)
		{
			current->pid = fork1(main);
			if (current->pid == 0)
			{
				if (i > 0)
				{
					if (dup2(main->parser->pipes[i - 1][0], STDIN_FILENO) == -1)
						dup_failed(main, main->parser->pipes[i - 1][0],
							STDIN_FILENO);
					if (close(main->parser->pipes[i - 1][0]) == -1)
						close_failed(main, main->parser->pipes[i - 1][0]);
				}
				if (current->next != NULL)
				{
					if (dup2(main->parser->pipes[i][1], STDOUT_FILENO) == -1)
						dup_failed(main, main->parser->pipes[i][1],
							STDOUT_FILENO);
					if (close(main->parser->pipes[i][1]) == -1)
						close_failed(main, main->parser->pipes[i][1]);
				}
				calling_redirects(main, current);
				return (current);
			}
		}
		if (i > 0) // for parent
			if (close(main->parser->pipes[i - 1][0]) == -1)
				close_failed(main, main->parser->pipes[i - 1][0]);
		if (current->next != NULL)
			if (close(main->parser->pipes[i][1]) == -1)
				close_failed(main, main->parser->pipes[i][1]);
		if (current->pid != 0)
		{
			i++;
			j++;
			current = current->next;
		}
	}
	return (main->cmd);
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

t_cmd	*init_pipes(t_main *main)
{
	t_cmd	*own_cmd;

	alloc_pipes(main);
	own_cmd = switching_fds(main);
	return (own_cmd);
}
