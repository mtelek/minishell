/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_words1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/27 22:36:37 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/28 00:24:15 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	last_word_check(char *input, int i, t_main *main)
{
	while (input[i])
	{
		if (!ft_isspace(input[i]) && !is_operator(input[i], input[i + 1],
				main->operators, main))
			return (1);
		i++;
	}
	return (0);
}

int	calc_i_w_quotes(char *input, int i)
{
	int	temp_i;

	temp_i = 0;
	if (input[i] == 34 || input[i] == 39)
	{
		temp_i = qoutes_handler(input, i);
		if (temp_i != 0)
			i = temp_i - 1;
	}
	return (i);
}

int	handle_spaces_and_operators(char *input, int i, int *n_words, t_main *main)
{
	if (last_word_check(input, i, main))
		(*n_words)++;
	else if ((input[i + 1] == '|' || input[i + 1] == '<' || input[i + 1] == '>')
		&& !input[i + 2])
		(*n_words)++;
	else if (input[i + 1] && input[i + 2] && ((input[i + 1] == '|' && input[i
					+ 2] == '|') || (input[i + 1] == '<' && input[i + 2] == '<')
			|| (input[i + 1] == '>' && input[i + 2] == '>')))
		(*n_words)++;
	while (input[i + 1] && ft_isspace(input[i + 1]))
		i++;
	return (i);
}

int	number_of_words(char *input, t_main *main)
{
	int	n_words;
	int	i;

	n_words = 0;
	i = 0;
	if (n_words == 0 && input[0] != '\0')
		n_words++;
	while (input[i] != '\0')
	{
		if (input[i] == 34 || input[i] == 39)
			i = calc_i_w_quotes(input, i);
		else if ((input[i] && ft_isspace(input[i])))
			i = handle_spaces_and_operators(input, i, &n_words, main);
		else if (checker_for_op_space(main, input, i))
			n_words = calc_n_words_for_op(input, n_words, i);
		else if (ops_check(input, i))
			n_words++;
		i++;
	}
	return (n_words);
}
