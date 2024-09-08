/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:55:47 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/08 10:09:20 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_value(char *env, char *var_equal, t_main *main)
{
	char	*value;

	value = ft_substr(env, ft_strlen(var_equal), ft_strlen(env));
	if (!value)
		error_function(22, main);
	return (value);
}

void	add_singles(t_expand_node *expand, t_main *main)
{
	char	*new_str;
	int		len;

	len = ft_strlen(expand->str);
	new_str = malloc(len + 3);
	if (!new_str)
		error_function(-1, main);
	new_str[0] = '\'';
	ft_strcpy(new_str + 1, expand->str);
	new_str[len + 1] = '\'';
	new_str[len + 2] = '\0';
	free(expand->str);
	expand->str = new_str;
}

void	str_check(t_expand_node *expand, t_main *main)
{
	if (!expand->str)
		error_function(-1, main);
}
