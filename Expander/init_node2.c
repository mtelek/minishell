/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:04:52 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 17:56:33 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_quote(t_expand_node **head, t_lexer *lexer, t_main *main,
			t_init_ex_node *state)
{
	char	*substr;

	if (state->in_quotes && lexer->str[state->i] == state->quote_char)
	{
		state->in_quotes = false;
		substr = ft_strndup(lexer->str + state->start,
				state->i - state->start + 1);
		if (!substr)
			error_function(-1, main);
		add_node(head, substr, main);
		state->start = state->i + 1;
	}
	else if (!state->in_quotes)
	{
		no_quotes(head, lexer, main, state);
		state->in_quotes = true;
		state->quote_char = lexer->str[state->i];
		state->start = state->i;
	}
}

void	handle_special_char(t_expand_node **head, t_lexer *lexer, t_main *main,
			t_init_ex_node *state)
{
	char	*substr;

	if (state->i > state->start)
	{
		substr = ft_strndup(lexer->str + state->start, state->i - state->start);
		if (!substr)
			error_function(-1, main);
		add_node(head, substr, main);
	}
	state->start = state->i;
}

void	handle_space(t_expand_node **head, t_lexer *lexer, t_main *main,
			t_init_ex_node *state)
{
	char	*substr;

	if (state->i > state->start)
	{
		substr = ft_strndup(lexer->str + state->start, state->i - state->start);
		if (!substr)
			error_function(-1, main);
		add_node(head, substr, main);
	}
	state->start = state->i + 1;
}

void	add_remaining_substring(t_expand_node **head, t_lexer *lexer,
		t_main *main, t_init_ex_node *state)
{
	char	*substr;

	if (state->i > state->start)
	{
		substr = ft_strndup(lexer->str + state->start, state->i - state->start);
		if (!substr)
			error_function(-1, main);
		add_node(head, substr, main);
	}
}

void	split_up_by_quotes(t_expand_node **head, t_lexer *lexer, t_main *main)
{
	t_init_ex_node	state;

	state.i = 0;
	state.start = 0;
	state.in_quotes = false;
	state.quote_char = '\0';
	while (lexer->str[state.i])
	{
		if (lexer->str[state.i] == '"' || lexer->str[state.i] == '\'')
		{
			handle_quote(head, lexer, main, &state);
		}
		else if (lexer->str[state.i] == '$' && !state.in_quotes)
		{
			handle_special_char(head, lexer, main, &state);
		}
		else if (lexer->str[state.i] == ' ' && !state.in_quotes)
			handle_space(head, lexer, main, &state);
		state.i = state.i +1;
	}
	add_remaining_substring(head, lexer, main, &state);
}
