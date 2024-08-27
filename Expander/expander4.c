/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:54:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/27 16:10:18 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	remove_one_char(t_expand_node *expand, t_main *main, int j)
{
	char *new_str;
	int i;
	int k;
	int len;

	i = 0;
	k = 0;
	len = ft_strlen(expand->str) - 1;
	new_str = malloc(len + 1);
	if (!new_str)
		error_function(24, main);
	while (expand->str[i])
	{
		if (i == j)
			i += 1;
		if (expand->str[i])
			new_str[k++] = expand->str[i++];
	}
	new_str[k] = '\0';
	free(expand->str);
	expand->str = new_str;
}

void	delete_all_doubles(t_expand_node *expand, t_main *main)
{
	int i;
	char *var_name;
	int len_var_name;
	int	n_double;
	int location_dollar;
	int  end_var;

	i = 0;
	var_name = find_var_name(expand->str, main);
	len_var_name = ft_strlen(var_name);
	location_dollar = find_character(expand->str, '$');
	end_var = location_dollar + len_var_name + 1;
	n_double = count_character_till_dollar(expand->str, 34);
	while (expand->str[i])
	{
		if (n_double % 2 == 0)
		{
			if (expand->str[i] == 34)
				remove_one_char(expand, main, i);
		}
		else if (n_double % 2 == 1)
		{
			if (expand->str[i] == 34 && expand->str[i-1] != '$' && expand->str[i+1] != '$' && i != end_var)
				remove_one_char(expand, main, i);
		}
		i++;
	}
}

