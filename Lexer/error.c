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

void	error_function(int error_type, t_operator *operators, t_lexer *lexer,
		t_cmd *cmd)
{
	error_operators(operators);
	error_lexer(error_type, lexer);
	error_cmd(error_type, cmd);
	if (error_type == 1)
		ft_putstr_fd(MF_OPERATOR, 2);
	else if (error_type == 2)
		ft_putstr_fd(MF_LEXER, 2);
	else if (error_type == 3)
		ft_putstr_fd(MF_WORD, 2);
	else if (error_type == 4)
		ft_putstr_fd(MF_CMD_TABLE, 2);
	else if (error_type == 5)
		ft_putstr_fd(MF_CMD_ARGS, 2);
	else if (error_type == 6)
		ft_putstr_fd(MF_CMD_CMD, 2);
	exit(2);
}
