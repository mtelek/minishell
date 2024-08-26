/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:54:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/26 21:56:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	remove_one_char(t_lexer *lexer, t_main *main, int j)
{
	char *new_str;
	int i;
	int k;
	int len;

	i = 0;
	k = 0;
	len = ft_strlen(lexer->str) - 1;
	new_str = malloc(len + 1);
	if (!new_str)
		error_function(24, main);
	while (lexer->str[i])
	{
		if (i == j)
			i += 1;
		if (lexer->str[i])
			new_str[k++] = lexer->str[i++];
	}
	new_str[k] = '\0';
	free(lexer->str);
	lexer->str = new_str;
}

void	delete_all_doubles(t_lexer *lexer, t_main *main)
{
	int i;
	char *var_name;
	int len_var_name;
	int	n_double;
	int location_dollar;
	int  end_var;

	i = 0;
	var_name = find_var_name(lexer->str, main);
	len_var_name = ft_strlen(var_name);
	location_dollar = find_character(lexer->str, '$');
	end_var = location_dollar + len_var_name + 1;
	n_double = count_character_till_dollar(lexer->str, 34);
	while (lexer->str[i])
	{
		if (n_double % 2 == 0)
		{
			if (lexer->str[i] == 34)
				remove_one_char(lexer, main, i);
		}
		else if (n_double % 2 == 1)
		{
			if (lexer->str[i] == 34 && lexer->str[i-1] != '$' && lexer->str[i+1] != '$' && i != end_var)
				remove_one_char(lexer, main, i);
		}
		i++;
	}
}

