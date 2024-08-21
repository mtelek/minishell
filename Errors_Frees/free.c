/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:42:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/21 14:26:49 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_exec(t_exec *exec)
{
	free(exec);
	exec = NULL;
}

void	free_parser(t_parser *parser)
{
	int	i;

	i = -1;
	if (!parser)
		return ;
	while (++i < parser->n_pipes)
	{
		if (parser->pipes[i])
		{
			free(parser->pipes[i]);
			parser->pipes[i] = NULL;
		}
	}
	free(parser->pipes);
	parser->pipes = NULL;
	free(parser);
	parser = NULL;
}

void	ok_free_function(t_main *main)
{
	if (main->operators)
		free_operator(main->operators);
	if (main->lexer)
		free_lexer(main->lexer);
	if (main->cmd)
		free_cmd(main->cmd);
	if (main->parser)
		free_parser(main->parser);
	if (main->exec)
		free_exec(main->exec);
}


void	syntax_free(t_main *main)
{
	free_operator(main->operators);
	free_lexer(main->lexer);
}