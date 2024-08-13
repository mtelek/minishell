/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/13 22:18:58 by mtelek           ###   ########.fr       */
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

void	alloc_parser(t_main *main)
{
	main->parser = malloc(sizeof(t_parser));
	if (!main->parser)
		error_function(7, main);
	main->parser->n_pipes = 0;
    main->parser->n_input_red = 0;
    main->parser->n_output_red = 0;
    main->parser->n_append_out = 0;
    main->parser->pipes = NULL;
}

void alloc_exec(t_main *main)
{
	main->exec = malloc(sizeof(t_exec));
	if (!main->exec)
		error_function(7, main); //def mallloc failure here
	main->exec->n_childs = 1;
}

void	count_operators(t_main *main)
{
	main->parser->n_pipes = count_cmds(main->lexer) - 1;
	main->parser->n_input_red = red_count(main->lexer, INPUT_RED);
	main->parser->n_output_red = red_count(main->lexer, OUTPUT_RED);
	main->parser->n_append_out = red_count(main->lexer, APPEND_OUT);
}

void	parser(t_main *main)
{
	t_cmd	*own_cmd;
	pid_t	pid; //should be _pid_t

	own_cmd = NULL;
	creating_cmd_table(main);
	alloc_parser(main);
	count_operators(main);
	alloc_exec(main);
	if (main->parser->n_pipes)
		own_cmd = init_pipes(main);
	if (main->parser->n_input_red)
		init_infile(main);
	if (main->parser->n_output_red)
		init_outfile(main);
	if (main->parser->n_append_out)
		init_append_out(main);
	if (!own_cmd)
	{
		pid = fork1(main);
		main->cmd->pid = pid;
		own_cmd = main->cmd;
	}
	else if (own_cmd)
		main->exec->n_childs = count_cmds(main->lexer);
	executor(main, own_cmd);
}
