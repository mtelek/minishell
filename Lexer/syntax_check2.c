/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:22:12 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/01 22:51:31 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

bool	dot_check(t_lexer *lexer, t_main *main)
{
	if ((lexer->str[0] == '.' && lexer->str[1] == '\0' && lexer->next == NULL)
		|| (lexer->str[0] == 34 && lexer->str[1] == '.' && lexer->str[2] == 34
			&& lexer->str[3] == '\0') || (lexer->str[0] == 39
			&& lexer->str[1] == '.' && lexer->str[2] == 39
			&& lexer->str[3] == '\0'))
	{
		ft_putstr_fd("bash: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (false);
	}
	if ((lexer->str[0] == '.' && lexer->str[1] == '.' && lexer->str[2] == '\0'
			&& lexer->next == NULL) || (lexer->str[0] == 34
			&& lexer->str[1] == '.' && lexer->str[2] == '.'
			&& lexer->str[3] == 34 && lexer->str[4] == '\0')
		|| (lexer->str[0] == 39 && lexer->str[1] == '.' && lexer->str[2] == '.'
			&& lexer->str[3] == 39 && lexer->str[4] == '\0'))
	{
		ft_putstr_fd("..: command not found\n", 2);
		main->exit_code = 127;
		return (false);
	}
	return (true);
}

int	find_next_character(char *str, int i, char c)
{
	if (str[i + 1])
		i++;
	else
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	inside_quote_check(t_lexer *lexer, int i, char c)
{
	int	next_quote;

	next_quote = find_next_character(lexer->str, i, c);
	if (next_quote == -1)
	{
		if (c == 34)
			ft_putstr_fd(ERR_QUOTE2, 2);
		else if (c == 39)
			ft_putstr_fd(ERR_QUOTE1, 2);
		return (-1);
	}
	i = next_quote;
	return (i);
}

bool	quote_check(t_lexer *lexer)
{
	int	i;

	while (lexer != NULL)
	{
		i = 0;
		while (lexer->str[i])
		{
			if (lexer->str[i] == 39)
				i = inside_quote_check(lexer, i, 39);
			else if (lexer->str[i] == 34)
				i = inside_quote_check(lexer, i, 34);
			if (i == -1)
				return (false);
			i++;
		}
		lexer = lexer->next;
	}
	return (true);
}

bool	checking_combinaton(t_lexer *lexer)
{
	if ((lexer->type == 3 && lexer->next->type == 2))
		return (ft_putstr_fd(ERROR_M_LESSER, 2), false);
	else if ((lexer->type == 2 && lexer->next->type == 1)
		|| (lexer->type == 3 && lexer->next->type == 1))
		return (ft_putstr_fd(ERROR_M_PIPE, 2), false);
	return (true);
}
