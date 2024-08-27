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
			return (PIPE);
		else if (!ft_strncmp(str, "<", 1))
			return (INPUT_RED);
		else if (!ft_strncmp(str, ">", 1))
			return (OUTPUT_RED);
	}
	else if (ft_strlen(str) == 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HEREDOC);
		else if (!ft_strncmp(str, ">>", 2))
			return (APPEND_OUT);
		else if (!ft_strncmp(str, "||", 2))
			return (7);
	}
	else
		return (6);
	return (6);
}

void	current_check(t_lexer *current, t_main *main)
{
	if (!current)
		error_function(2, main);
}

int	get_tokens(char *input, t_lexer **lexer, t_main *main)
{
	int		n_words;
	int		i;
	t_lexer	*current;
	t_lexer	*prev_node;

	prev_node = NULL;
	i = 0;
	n_words = number_of_words(input, main);
	if (n_words == 0)
		return (-1);
	while (i++ < n_words)
	{
		current = malloc(sizeof(t_lexer));
		current_check(current, main);
		current->str = getting_word(input, main);
		current->type = get_type(current->str);
		current->next = NULL;
		current->prev = prev_node;
		if (prev_node)
			prev_node->next = current;
		else
			*lexer = current;
		prev_node = current;
	}
	return (0);
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
	current = NULL;
	prev_node = NULL;
}

void	init_operators(t_operator **head, t_main *main)
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
			error_function(1, main);
		current->operator = ft_strdup(signs[i]);
		if (!current->operator)
			error_function(1, main);
		current->type = i + 1;
		if (i == 5)
			current->type = 7;
		creating_l_list(current, &prev_node, head);
	}
}
