/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:57:12 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/07 23:17:35 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_lexer_str(t_lexer *lexer)
{
	free(lexer->str);
	lexer->str = NULL;
}

char	*create_substr(t_lexer *lexer, int i, int start, t_main *main)
{
	char	*substr;

	substr = ft_strndup(lexer->str + start, i - start);
	if (!substr)
		error_function(-1, main);
	return (substr);
}

void	no_quotes(t_expand_node **head, t_lexer *lexer,
			t_main *main, t_init_ex_node *state)
{
	char	*substr;

	if (state->i > state->start)
	{
		substr = ft_strndup(lexer->str + state->start,
				state->i - state->start);
		if (!substr)
			error_function(-1, main);
		add_node(head, substr, main);
	}
}
