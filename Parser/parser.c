/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/10 23:57:57 by mtelek           ###   ########.fr       */
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
}

void	parser(t_main *main)
{
	int i;
	t_cmd *own_cmd;

	i = 0;
	creating_cmd_table(main);
	alloc_parser(main);
	main->parser->n_pipes = count_cmds(main->lexer) - 1;
	main->parser->n_input_red = red_count(main->lexer, INPUT_RED);
	main->parser->n_output_red = red_count(main->lexer, OUTPUT_RED);
	main->parser->n_append_out = red_count(main->lexer, APPEND_OUT);
	if (main->parser->n_pipes)
		own_cmd = init_pipes(main);
	if (main->parser->n_input_red)
		init_infile(main);
	if (main->parser->n_output_red)
		init_outfile(main);
	if (main->parser->n_append_out)
		init_append_out(main);
	if (main->parser->n_pipes == 0)
	{
		if (main->cmd->cmd)
		{
			execvp(main->cmd->cmd, main->cmd->args);
			perror("execvp");
			exit(1);
		}
	}
	else if (main->parser->n_pipes != 0)
	{
		execvp(own_cmd->cmd, own_cmd->args);
		perror("execvp");
		exit(1);
	}
	while (i++ < main->parser->n_pipes)
		wait(0);
}
