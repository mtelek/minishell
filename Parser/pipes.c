/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:16:28 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/08 00:45:20 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_fds(t_main *main, t_cmd *current, int i)
{
	if (i > 0)
	{
		if (dup2(main->parser->pipes[i - 1][0], STDIN_FILENO) == -1)
			dup_failed(main, main->parser->pipes[i - 1][0], STDIN_FILENO);
		if (close(main->parser->pipes[i - 1][0]) == -1)
			close_failed(main, main->parser->pipes[i - 1][0]);
	}
	if (current->next != NULL)
	{
		if (dup2(main->parser->pipes[i][1], STDOUT_FILENO) == -1)
			dup_failed(main, main->parser->pipes[i][1], STDOUT_FILENO);
		if (close(main->parser->pipes[i][1]) == -1)
			close_failed(main, main->parser->pipes[i][1]);
	}
}

t_cmd	*process_command(t_main *main, t_cmd *current, int *i, int *j)
{
	current->pid = fork1(main);
	if (current->pid == 0)
	{
		handle_fds(main, current, *i);
		calling_redirects(main, current);
		return (current);
	}
	if (*i > 0)
		if (close(main->parser->pipes[*i - 1][0]) == -1)
			close_failed(main, main->parser->pipes[*i - 1][0]);
	if (current->next != NULL)
		if (close(main->parser->pipes[*i][1]) == -1)
			close_failed(main, main->parser->pipes[*i][1]);
	(*i)++;
	(*j)++;
	return (current->next);
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
			current = process_command(main, current, &i, &j);
			if (current && current->pid == 0)
				return (current);
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
