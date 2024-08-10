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

int	qoutes_checker(char *input, char check, int i)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == check)
			return (i);
		i++;
	}
	return (0);
}

int	qoutes_handler(char *input, int i)
{
	int	temp_i;

	temp_i = 0;
	if (input[i] == 34)
	{
		temp_i = qoutes_checker(input, 34, i);
		if (temp_i != 0)
			i = temp_i;
	}
	else if (input[i] == 39)
	{
		temp_i = qoutes_checker(input, 39, i);
		if (temp_i != 0)
			i = temp_i;
	}
	i++;
	return (i);
}

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

int	number_of_words(char *input, t_main *main) // hopefully its correct now
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
		{
			if (last_word_check(input, i, main))
				n_words++;
			else if ((input[i + 1] == '|' || input[i + 1] == '<' || input[i
						+ 1] == '>') && !input[i + 2])
				n_words++;
			else if (input[i + 1] && input[i + 2] && ((input[i + 1] == '|'
						&& input[i + 2] == '|') || (input[i + 1] == '<'
						&& input[i + 2] == '<') || (input[i + 1] == '>'
						&& input[i + 2] == '>')))
				n_words++;
			while (input[i + 1] && ft_isspace(input[i + 1]))
				i++;
		}
		else if (checker_for_op_space(main, input, i))
			n_words = calc_n_words_for_op(input, n_words, i);
		else if (ops_check(input, i))
			n_words++;
		i++;
	}
	// printf("N_WORDS:%d\n", n_words);
	return (n_words);
}
