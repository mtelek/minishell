/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 23:03:21 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	red_count(t_lexer *lexer, int type)
{
	int	counter;

	counter = 0;
	while (lexer != NULL)
	{
		if (lexer->type == type)
			counter++;
		lexer = lexer->next;
	}
	return (counter);
}

void	calling_redirects(t_main *main, t_cmd *own_cmd)
{
	if (own_cmd->pid == 0)
	{
		printf("IN: %d, OUT: %d, APPEND: %d\n", own_cmd->n_in, own_cmd->n_out,
			own_cmd->n_append);
		if (own_cmd->n_in)
			init_infile(main, own_cmd);
		if (own_cmd->n_out)
			init_outfile(main, own_cmd);
		if (own_cmd->n_append)
			init_append_out(main, own_cmd);
	}
}

void	wait_for_children(t_main *main)
{
	int	i;
	int	status;
	int	exit_status;

	status = 0;
	exit_status = 0;
	i = 0;
	while (i < main->exec->n_childs)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			main->exit_code = exit_status;
		}
		i++;
	}
}

void	parser(t_main *main)
{
	t_cmd	*own_cmd;
	__pid_t	pid;

	own_cmd = NULL;
	creating_cmd_table(main);
	alloc_parser(main);
	alloc_exec(main);
	if (main->parser->n_pipes)
	{
		own_cmd = init_pipes(main);
		wait_for_children(main);
		executor(main, own_cmd);
	}
	else if (main->parser->n_pipes == 0)
	{
		pid = fork1(main);
		main->cmd->pid = pid;
		own_cmd = main->cmd;
		calling_redirects(main, own_cmd);
		wait_for_children(main);
		executor(main, own_cmd);
	}
}
