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

bool	checking_lex(char *str, t_main *main)
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
				return (ft_putstr_fd(ERR_QUOTE2, 2, main), false);
		}
		else if (str[i] == 39)
		{
			temp_i = qoutes_checker(str, 39, i);
			if (temp_i != -1)
				i = temp_i;
			if (temp_i == -1)
				return (ft_putstr_fd(ERR_QUOTE1, 2, main), false);
		}
		i++;
	}
	return (true);
}

bool	checking_combinaton(t_lexer *lexer, t_main *main)
{
	if ((lexer->type == 3 && lexer->next->type == 2))
		return (ft_putstr_fd(ERROR_M_LESSER, 2, main), false);
	else if ((lexer->type == 2 && lexer->next->type == 1)
		|| (lexer->type == 3 && lexer->next->type == 1))
		return (ft_putstr_fd(ERROR_M_PIPE, 2, main), false);
	return (true);
}

bool	syntax_doubles_diff(t_lexer *lexer, t_main *main)
{
	while (lexer != NULL)
	{
		if (lexer->next && lexer->type < 6 && lexer->next->type < 6)
			if (checking_combinaton(lexer, main) == false)
				return (false);
		if (lexer->type < 6 && !lexer->next)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2, main), false);
		lexer = lexer->next;
	}
	return (true);
}

bool	syntax_doubles_same(t_lexer *lexer, t_main *main)
{
	while (lexer != NULL)
	{
		if (lexer->type == 7)
			return (ft_putstr_fd(ERROR_M_PIPE, 2, main), false);
		if (lexer->type < 6 && lexer->next == NULL)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2, main), false);
		if (checking_lex(lexer->str, main) == false)
			return (false);
		lexer = lexer->next;
	}
	return (true);
}

bool	syntax_check(t_lexer *lexer, t_main *main)
{
	if (lexer->type == 1)
		return (ft_putstr_fd(ERROR_M_PIPE, 2, main), false);
	if (lexer != NULL && lexer->next == NULL)
		if (lexer->type < 6)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2, main), false);
	if (syntax_doubles_diff(lexer, main) == false)
		return (false);
	if (syntax_doubles_same(lexer, main) == false)
		return (false);
	return (true);
}
