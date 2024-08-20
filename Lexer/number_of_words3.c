/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_words3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:45:50 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 21:13:04 by mtelek           ###   ########.fr       */
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

int	calc_n_words_w_op(int n_words, char *input, int i)
{
	n_words++;
	if (input[i + 1] && !ft_isspace(input[i + 1]))
		n_words++;
	return (n_words);
}

int	calc_n_words_for_op(char *input, int n_words, int i)
{
	if (input[i + 1] != '|' && input[i + 1] != '<'
		&& input[i + 1] != '>')
		n_words++;
	return (n_words);
}

int	checker_for_op_space(t_main *main, char *input, int i)
{
	if (input[i + 1] && (input[i] == '|' || input[i] == '<'
			|| input[i] == '>') && !ft_isspace(input[i + 1])
		&& !is_operator(input[i + 1], input[i + 2], main->operators, main))
		return (1);
	else
		return (0);
}
