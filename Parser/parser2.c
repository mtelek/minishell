/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:56:11 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/28 23:40:29 by mtelek           ###   ########.fr       */
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

void	alloc_builtin(t_main *main)
{
	main->builtin = malloc(sizeof(t_builtin));
	if (!main->builtin)
		error_function(12, main);
	main->builtin->export = NULL;
}

void	alloc_parser(t_main *main)
{
	main->parser = malloc(sizeof(t_parser));
	if (!main->parser)
		error_function(7, main);
	main->parser->n_pipes = count_cmds(main->lexer) - 1;
	main->parser->pipes = 0;
	main->parser->output_fd = 0;
	main->parser->append_out_fd = 0;
	main->parser->heredoc_fd = 0;
	main->parser->input_fd = 0;
} 

void	alloc_exec(t_main *main)
{
	main->exec = malloc(sizeof(t_exec));
	if (!main->exec)
		error_function(14, main);
	main->exec->n_childs = count_cmds(main->lexer);
}

void	parser_helper(t_main *main)
{
	creating_cmd_table(main);
	alloc_parser(main);
	find_hd_indicator(main, main->cmd);
	alloc_exec(main);
	alloc_builtin(main);
}
