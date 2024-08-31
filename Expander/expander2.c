/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:46:49 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/01 00:10:37 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	no_var_name_found(t_expand_node *current, t_main *main)
{
	free(current->str);
	current->str = ft_strdup("");
	if (!current->str)
		error_function(-1, main);
}

void	remove_dollar_sign(t_expand_node *expand, t_main *main)
{
	char	*new_str;

	new_str = malloc(1);
	if (!new_str)
		error_function(23, main);
	new_str[0] = '\0';
	free(expand->str);
	expand->str = new_str;
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
	int	dollar_sign;

	dollar_sign = find_character(str, '$');
	if (dollar_sign == -1)
		return (false);
	if (!ft_strcmp(str, "$"))
		return (false);
	if (str[0] == 39)
		return (false);
	if (str[0 == 34])
		return (true);
	if (find_character(str, 34) == -1 && find_character(str, 39) == -1)
		return (true);
	return (false);
}

void	cutting_up_lexer_str(t_expand_node **head, t_lexer *lexer, t_main *main)
{
	if (find_character(lexer->str, 34) == -1
		&& find_character(lexer->str, 39) == -1)
		split_up_by_dollar(head, lexer, main);
	else
		split_up_by_quotes(head, lexer, main);
}
