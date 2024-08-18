/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:56:11 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/17 18:50:15 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	alloc_builtin(t_main *main)
{
	main->builtin = malloc(sizeof(t_builtin));
	if (!main->builtin)
		error_function(-1, main); //another error_type needed
	main->builtin->export = NULL;
}

void	alloc_parser(t_main *main)
{
	main->parser = malloc(sizeof(t_parser));
	if (!main->parser)
		error_function(7, main);
	main->parser->n_pipes = count_cmds(main->lexer) - 1;
	main->parser->pipes = NULL;
}

void	alloc_exec(t_main *main)
{
	main->exec = malloc(sizeof(t_exec));
	if (!main->exec)
		error_function(7, main); //another error_type needed
	main->exec->n_childs = count_cmds(main->lexer);
}