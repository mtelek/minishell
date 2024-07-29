/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_words1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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

int	checking_for_doubles(char *input, int i)
{
	if (input[i + 1] && input[i])
	{
		if ((!ft_strncmp(&input[i + 1], "<", 1) && !ft_strncmp(&input[i], "<",
					1)) || (!ft_strncmp(&input[i + 1], ">", 1)
				&& !ft_strncmp(&input[i], ">", 1)) || (!ft_strncmp(&input[i
						+ 1], "|", 1) && !ft_strncmp(&input[i], "|", 1)))
		{
			i++;
		}
		i++;
	}
	return (i);
}

int	number_of_words(char *input, t_operator *operators)
{
	int	i;
	int	n_words;

	i = 0;
	n_words = 0;
	while (input[i] != '\0')
	{
		while (input[i] != '\0' && ft_isspace(input[i]))
			i++;
		if (input[i] != '\0' && !is_operator(input[i], input[i + 1], operators))
			n_words++;
		while (input[i] != '\0' && !ft_isspace(input[i])
			&& !is_operator(input[i], input[i + 1], operators))
			i = qoutes_handler(input, i);
		while (input[i] != '\0' && ft_isspace(input[i])
			&& !is_operator(input[i], input[i + 1], operators))
			i++;
		while (input[i] && is_operator(input[i], input[i + 1], operators))
		{
			n_words++;
			i = checking_for_doubles(input, i);
		}
	}
	return (n_words);
}
