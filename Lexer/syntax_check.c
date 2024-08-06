/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:22:57 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:25:56 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

bool	checking_lex(char *str)
{
	int	i;
	int	temp_i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			temp_i = qoutes_checker(str, 34, i);
			if (temp_i != -1)
				i = temp_i;
			if (temp_i == -1)
				return (ft_putstr_fd(ERR_QUOTE2, 2), false);
		}
		else if (str[i] == 39)
		{
			temp_i = qoutes_checker(str, 39, i);
			if (temp_i != -1)
				i = temp_i;
			if (temp_i == -1)
				return (ft_putstr_fd(ERR_QUOTE1, 2), false);
		}
		i++;
	}
	return (true);
}

bool	checking_combinaton(t_lexer *lexer)
{
	if ((lexer->type == 1 && lexer->next->type == 3) || (lexer->type == 3
			&& lexer->next->type == 1) || (lexer->type == 1
			&& lexer->next->type == 2) || (lexer->type == 2
			&& lexer->next->type == 3) || (lexer->type == 1
			&& lexer->next->type == 4) || (lexer->type == 1
			&& lexer->next->type == 5))
	{
		ft_putstr_fd(ERROR_M_NEWLINE, 2);
		return (false);
	}
	return (true);
}

bool	syntax_doubles_diff(t_lexer *lexer)
{
	while (lexer->next != NULL)
	{
		if ((lexer->type < 6 && lexer->type != 1) && lexer->next->type < 6)
		{
			if (checking_combinaton(lexer) == false)
				return (false);
			if (lexer->next->type == 1)
				ft_putstr_fd(ERROR_M_PIPE, 2);
			else if (lexer->next->type == 2)
				ft_putstr_fd(ERROR_M_LESSER, 2);
			else if (lexer->next->type == 3)
				ft_putstr_fd(ERROR_M_GREATER, 2);
			else if (lexer->next->type == 4)
				ft_putstr_fd(ERROR_M_LESSERP, 2);
			else if (lexer->next->type == 5)
				ft_putstr_fd(ERROR_M_GREATERP, 2);
			return (false);
		}
		lexer = lexer->next;
	}
	return (true);
}

bool	syntax_doubles_same(t_operator *temp_op, t_lexer *lexer,
		t_lexer *temp_lex)
{
	while (temp_op != NULL)
	{
		if (lexer->type < 6 && lexer->next->type == temp_op->type)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2), false);
		temp_op = temp_op->next;
	}
	while (temp_lex != NULL)
	{
		if (temp_lex->type == 7)
		{
			ft_putstr_fd(ERROR_M_PIPE, 2);
			return (false);
		}
		if (temp_lex->type < 6 && temp_lex->next == NULL)
		{
			ft_putstr_fd(ERROR_M_NEWLINE, 2);
			return (false);
		}
		if (checking_lex(temp_lex->str) == false)
			return (false);
		temp_lex = temp_lex->next;
	}
	return (true);
}

bool	syntax_check(t_operator *operators, t_lexer *lexer)
{
	t_operator	*temp_op;
	t_lexer		*temp_lex;

	temp_op = operators;
	temp_lex = lexer;
	if (temp_lex->type == 1)
	{
		ft_putstr_fd(ERROR_M_PIPE, 2);
		return (false);
	}
	if (lexer != NULL && lexer->next == NULL)
	{
		if (lexer->type < 6)
		{
			ft_putstr_fd(ERROR_M_NEWLINE, 2);
			return (false);
		}
	}
	if (syntax_doubles_diff(lexer) == false)
		return (false);
	if (syntax_doubles_same(temp_op, lexer, temp_lex) == false)
		return (false);
	return (true);
}
