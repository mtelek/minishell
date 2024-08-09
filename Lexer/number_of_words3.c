/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_words3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:45:50 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/09 23:31:29 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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
