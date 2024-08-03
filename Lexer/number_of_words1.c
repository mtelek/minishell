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

int	is_single_operator(char c, t_operator *operators)
{
	t_operator	*current;
	char		temp[2];

	temp[0] = c;
	temp[1] = '\0';
	current = operators;
	while (current)
	{
		if (ft_strcmp(current->operator, temp) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

//! more than 25 lines, should split it

int	number_of_words(char *input, t_operator *operators)
{
	int	i;
	int	n_words;
	int	in_word;

	i = 0;
	n_words = 0;
	in_word = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if ((i > 0 && ft_isspace(input[i - 1])) || i == 0)
				n_words++;
			i = qoutes_handler(input, i);
			in_word = 0;
		}
		else if (input[i] && ft_isspace(input[i]))
		{
			if (in_word)
			{
				n_words++;
				in_word = 0;
			}
		}
		else if (input[i] && input[i + 1] && ((input[i] == '|' && input[i
						+ 1] == '|') || (input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<')))
		{
			if (in_word)
			{
				n_words++;
				in_word = 0;
			}
			n_words++;
			i++;
		}
		else if (is_single_operator(input[i], operators))
		{
			if (in_word)
			{
				n_words++;
				in_word = 0;
			}
			n_words++;
		}
		else if (!in_word)
			in_word = 1;
		if (input[i])
			i++;
	}
	if (in_word)
		n_words++;
	printf("N_WORDS:%d\n", n_words);
	return (n_words);
}
