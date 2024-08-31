/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:42:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/01 00:32:30 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_main(t_main *main)
{
	int	i;

	i = 0;
	if (main == NULL)
		return ;
	if (main->env_array)
	{
		while (main->env_array[i] != NULL)
		{
			free(main->env_array[i]);
			i++;
		}
		free(main->env_array);
		main->env_array = NULL;
	}
}

void	free_exec(t_exec *exec)
{
	if (exec == NULL)
		return ;
	free(exec);
	exec = NULL;
}

void	free_parser(t_parser *parser)
{
	int	i;

	i = -1;
	if (parser == NULL)
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
	if (main->cmd)
		free_cmd(main->cmd);
	if (main->lexer)
		free_lexer(main->lexer);
	if (main->parser)
		free_parser(main->parser);
	if (main->exec)
		free_exec(main->exec);
	if (main->builtin)
		free_builtin(main->builtin);
}

void	syntax_free(t_main *main)
{
	free_operator(main->operators);
	free_lexer(main->lexer);
}
