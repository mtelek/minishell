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

bool	syntax_check_part2(t_lexer *lexer)
{
	if (lexer->next && (lexer->type == HEREDOC
			|| lexer->type == APPEND_OUT) && lexer->next->type == PIPE)
		return (ft_putstr_fd(ERROR_M_PIPE, 2), false);
	if (lexer->next && lexer->type == INPUT_RED
		&& lexer->next->type == OUTPUT_RED)
		return (ft_putstr_fd(ERROR_M_LESSER, 2), false);
	if (lexer->next && lexer->type == OUTPUT_RED
		&& lexer->next->type == OUTPUT_RED)
		return (ft_putstr_fd(ERROR_M_GREATER, 2), false);
	return (true);
}

bool	syntax_doubles_diff(t_lexer *lexer)
{
	while (lexer != NULL)
	{
		if (lexer->next && lexer->type < 6 && lexer->next->type < 6)
			if (checking_combinaton(lexer) == false)
				return (false);
		if (lexer->type < 6 && !lexer->next)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2), false);
		if (lexer->prev && lexer->type == HEREDOC
			&& (lexer->prev->type == OUTPUT_RED
				|| lexer->prev->type == APPEND_OUT))
			return (ft_putstr_fd(ERROR_M_LESSERP, 2), false);
		if (lexer->prev && lexer->type == OUTPUT_RED
			&& lexer->prev->type == HEREDOC)
			return (ft_putstr_fd(ERROR_M_GREATER, 2), false);
		if (lexer->next && lexer->type == HEREDOC && lexer->next->type == PIPE)
			return (ft_putstr_fd(ERROR_M_PIPE, 2), false);
		if (lexer->next && lexer->type == HEREDOC
			&& lexer->next->type == APPEND_OUT)
			return (ft_putstr_fd(ERROR_M_GREATERP, 2), false);
		if (syntax_check_part2(lexer) == false)
			return (false);
		lexer = lexer->next;
	}
	return (true);
}

bool	syntax_doubles_same(t_lexer *lexer)
{
	while (lexer != NULL)
	{
		if (lexer->type == 7)
			return (ft_putstr_fd(ERROR_M_PIPE, 2), false);
		if (lexer->type < 6 && lexer->next == NULL)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2), false);
		lexer = lexer->next;
	}
	return (true);
}

bool	syntax_check(t_lexer *lexer, t_main *main)
{
	if (lexer->type == 1)
		return (ft_putstr_fd(ERROR_M_PIPE, 2), false);
	if (lexer != NULL && lexer->next == NULL)
		if (lexer->type < 6)
			return (ft_putstr_fd(ERROR_M_NEWLINE, 2), false);
	if (syntax_doubles_diff(lexer) == false)
		return (false);
	if (syntax_doubles_same(lexer) == false)
		return (false);
	if (dot_check(lexer, main) == false)
		return (false);
	if (quote_check(lexer) == false)
		return (false);
	return (true);
}
