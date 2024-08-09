/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:52:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/02 19:52:41 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	error_operators(t_operator *operators)
{
	t_operator	*tmp_op;

	while (operators != NULL)
	{
		tmp_op = operators;
		operators = operators->next;
		free(tmp_op->operator);
		free(tmp_op);
	}
}

void	error_lexer(int error_type, t_lexer *lexer)
{
	t_lexer		*tmp_lex;

	if (error_type > 1)
	{
		while (lexer != NULL)
		{
			tmp_lex = lexer;
			lexer = lexer->next;
			free(tmp_lex->str);
			free(tmp_lex);
		}
	}
}

void	error_cmd(int error_type, t_cmd *cmd)
{
	t_cmd		*tmp_cmd;

	if (error_type > 3)
	{
		while (cmd != NULL)
		{
			tmp_cmd = cmd;
			cmd = cmd->next;
			free(tmp_cmd->args);
			free(tmp_cmd->cmd);
			free(tmp_cmd);
		}
	}
}

void	error_parser(int error_type, t_parser *parser)
{
	int	i;

	i = -1;
	if (error_type > 7)
		free(parser);
	while (parser->pipes[++i])
		free(parser->pipes[i]);
}

void	error_function(int error_type, t_main *main)
{
	error_operators(main->operators);
	error_lexer(error_type, main->lexer);
	error_cmd(error_type, main->cmd);
	error_parser(error_type, main->parser);
	if (error_type <= 10)
		error_type10(error_type);
	else if (error_type <= 20 && error_type > 10)
		error_type20(error_type);
	exit(2);
}
