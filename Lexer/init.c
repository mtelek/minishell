/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:26:39 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/28 00:07:02 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	get_type(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (!ft_strncmp(str, "|", 1))
			return (1);
		else if (!ft_strncmp(str, "<", 1))
			return (2);
		else if (!ft_strncmp(str, ">", 1))
			return (3);
	}
	else if (ft_strlen(str) == 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (4);
		else if (!ft_strncmp(str, ">>", 2))
			return (5);
		else if (!ft_strncmp(str, "||", 2))
			return (7);
	}
	else
		return (6);
	return (6);
}

void	get_tokens(char *input, t_operator *operators, t_lexer **lexer)
{
	int		n_words;
	int		i;
	t_lexer	*current;
	t_lexer	*prev_node;

	prev_node = NULL;
	i = 0;
	n_words = number_of_words(input, operators);
	while (i < n_words)
	{
		current = malloc(sizeof(t_lexer));
		if (!current)
			error_function(2, operators, current);
		current->str = getting_word(input, operators, current);
		current->type = get_type(current->str);
		current->next = NULL;
		current->prev = prev_node;
		if (prev_node)
			prev_node->next = current;
		else
			*lexer = current;
		prev_node = current;
		i++;
	}
}

void	creating_l_list(t_operator *current, t_operator **prev_node,
		t_operator **head)
{
	current->next = NULL;
	current->prev = *prev_node;
	if (*prev_node)
		(*prev_node)->next = current;
	else
		*head = current;
	*prev_node = current;
}

void	init_operators(t_operator **head)
{
	const char	*signs[] = {"|", "<", ">", "<<", ">>", "||"};
	t_operator	*prev_node;
	t_operator	*current;
	int			i;

	prev_node = NULL;
	i = -1;
	while (++i < 6)
	{
		current = malloc(sizeof(t_operator));
		if (!current)
			error_function(1, *head, NULL);
		current->operator = ft_strdup(signs[i]);
		if (!current->operator)
			error_function(1, *head, NULL);
		current->type = i + 1;
		if (i == 5)
			current->type = 7;
		creating_l_list(current, &prev_node, head);
	}
}
