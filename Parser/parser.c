/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:54:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/09 23:09:14 by mtelek           ###   ########.fr       */
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
	creating_cmd_table(main);
	// print_cmd_table(main->cmd);
	alloc_parser(main);
	main->parser->n_pipes = count_cmds(main->lexer) - 1;
	main->parser->n_input_red = red_count(main->lexer, INPUT_RED);
	main->parser->n_output_red = red_count(main->lexer, OUTPUT_RED);
	main->parser->n_append_out = red_count(main->lexer, APPEND_OUT);
	if (main->parser->n_pipes)
		init_pipes(main);
	if (main->parser->n_input_red)
		init_infile(main);
	if (main->parser->n_output_red)
		init_outfile(main);
	if (main->parser->n_append_out)
		init_append_out(main);
}
