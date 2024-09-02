/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:52:05 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/02 02:16:46 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	expand_exit_code(t_expand_node *current, t_main *main)
{
	free(current->str);
	current->str = ft_strdup(ft_itoa(main->exit_code));
	if (!current->str)
		error_function(-1, main);
}

void	init_current(t_lexer *lexer, t_main *main,
			t_expand_node **expand, t_expand_node **current)
{
	*expand = NULL;
	cutting_up_lexer_str(expand, lexer, main);
	*current = *expand;
	(*current)->single_flag = 0;
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
