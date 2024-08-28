/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:52:05 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/28 16:18:28 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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

void	cross_out_quotes(t_expand_node *expand, t_main *main, char c)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(expand->str) - count_character(expand->str, c);
	new_str = malloc(len + 1);
	if (!new_str)
		error_function(-1, main);
	while (expand->str[i])
	{
		if (expand->str[i] != c)
		{
			new_str[j] = expand->str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(expand->str);
	expand->str = new_str;
}

void	remove_all_quotes(t_expand_node *expand, t_main *main)
{
	int	check_single;
	int	check_double;

	check_single = find_character(expand->str, 39);
	check_double = find_character(expand->str, 34);
	if (check_single != -1)
		cross_out_quotes(expand, main, 39);
	else if (check_double != -1)
		cross_out_quotes(expand, main, 34);
}
