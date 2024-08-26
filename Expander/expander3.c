/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:52:05 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/26 21:55:48 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	count_character_till_dollar(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '$')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	count_character(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	cross_out_quotes(t_lexer *lexer, t_main *main, char c)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(lexer->str) - count_character(lexer->str, c);
	new_str = malloc(len + 1);
	if (!new_str)
		error_function(-1, main);
	while (lexer->str[i])
	{
		if (lexer->str[i] != c)
		{
			new_str[j] = lexer->str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(lexer->str);
	lexer->str = new_str;
}

void	remove_all_quotes(t_lexer *lexer, t_main *main)
{
	int	check_single;
	int	check_double;

	check_single = find_character(lexer->str, 39);
	check_double = find_character(lexer->str, 34);
	if (check_single != -1)
		cross_out_quotes(lexer, main, 39);
	else if (check_double != -1)
		cross_out_quotes(lexer, main, 34);
}

void	remove_two_char(t_lexer *lexer, t_main *main, int j)
{
	char	*new_str;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = ft_strlen(lexer->str) - 2;
	new_str = malloc(len + 1);
	if (!new_str)
		error_function(24, main);
	while (lexer->str[i])
	{
		if (i == j)
			i += 2;
		if (lexer->str[i])
			new_str[k++] = lexer->str[i++];
	}
	new_str[k] = '\0';
	free(lexer->str);
	lexer->str = new_str;
}

void	unused_quotes_removal(t_lexer *lexer, t_main *main)
{
	int	i;

	i = 0;
	while (lexer->str[i])
	{
		if ((lexer->str[i] == 39 && lexer->str[i + 1] == 39)
			|| (lexer->str[i] == 34 && lexer->str[i + 1] == 34))
		{
			remove_two_char(lexer, main, i);
			i--;
		}
		i++;
	}
}
