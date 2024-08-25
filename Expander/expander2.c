/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:46:49 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/25 23:03:38 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	remove_dollar_sign(int dollar_sign_index, t_lexer *lexer, t_main *main)
{
	char	*new_str;
	int		len;

	len = ft_strlen(lexer->str);
	new_str = malloc(len - 1);
	if (!new_str)
		error_function(23, main);
	ft_strlcpy(new_str, lexer->str, dollar_sign_index + 1);
	ft_strlcpy(new_str + dollar_sign_index, lexer->str + dollar_sign_index + 1,
		len - dollar_sign_index);
	free(lexer->str);
	lexer->str = new_str;
}

void	pinpoint_dollar_sign(t_lexer *lexer, t_main *main)
{
	int	s_single;
	int	e_single;
	int	dollar_sign;

	dollar_sign = find_character(lexer->str, '$');
	if (dollar_sign == -1)
		return ;
	s_single = qoutes_checker(lexer->str, 39, -1);
	e_single = qoutes_checker(lexer->str, 39, s_single);
	if (s_single != 0 && s_single > dollar_sign)
		remove_dollar_sign(dollar_sign, lexer, main);
	else if (lexer->str[0] != 39)
		remove_dollar_sign(dollar_sign, lexer, main);
}

int	find_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

bool	expander_check(char *str)
{
	int	s_single;
	int	e_single;
	int	s_double;
	int	e_double;
	int	dollar_sign;

	dollar_sign = find_character(str, '$');
	if (dollar_sign == -1)
		return (false);
	s_single = qoutes_checker(str, 39, -1);
	e_single = qoutes_checker(str, 39, s_single);
	s_double = qoutes_checker(str, 34, -1);
	e_double = qoutes_checker(str, 34, s_double);
	if ((s_single < s_double && s_single != 0) || str[0] == 39)
		if (dollar_sign < s_single || dollar_sign > e_single)
			return (true);
	if ((s_double < s_single && s_double != 0) || str[0] == 34)
		if (dollar_sign > s_double && dollar_sign < e_double)
			return (true);
	if (s_single == 0 && s_double == 0 && str[0] != 34 && str[0] != 39)
		return (true);
	return (false);
}
