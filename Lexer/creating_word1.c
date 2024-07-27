/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_word1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:30:00 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:25:43 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*creating_string(int start, int end, char *input)
{
	char	*word;
	int		k;

	k = 0;
	word = malloc((end - start) + 1);
	if (!word)
		return (0);
	while (start < end)
		word[k++] = input[start++];
	word[k] = '\0';
	return (word);
}

int	calculating_end(char *input, int i, t_operator *operators)
{
	int	temp_i;

	temp_i = 0;
	while (input[i] != '\0' && !ft_isspace(input[i]) && !is_operator(input[i],
			input[i + 1], operators))
	{
		if (input[i] == 34)
			temp_i = qoutes_checker(input, 34, i);
		if (input[i] == 39)
			temp_i = qoutes_checker(input, 39, i);
		if (temp_i != 0)
		{
			i = temp_i + 1;
			temp_i = 0;
		}
		else
			i++;
	}
	return (i);
}

char	*creating_word_wout_o(char *input, int i, t_operator *operators,
		t_lexer *lexer)
{
	int		start;
	int		end;
	char	*word;

	start = i;
	end = calculating_end(input, i, operators);
	i = end;
	if (start == end)
		return (NULL);
	word = creating_string(start, end, input);
	if (!word)
		error_function(3, operators, lexer);
	return (word);
}

char	*getting_word(char *input, t_operator *operators, t_lexer *lexer)
{
	static int	i;
	int			start;
	int			end;
	char		*word;

	i = getting_word_i_start(input, i);
	if (is_operator(input[i], input[i + 1], operators))
	{
		start = i;
		if ((input[i + 1] && ((input[i + 1] == '<' && input[i] == '<')
					|| (input[i + 1] == '>' && input[i] == '>') || (input[i
							+ 1] == '|' && input[i] == '|'))))
			i++;
		end = ++i;
		word = creating_string(start, end, input);
		if (!word)
			error_function(3, operators, lexer);
	}
	else
	{
		word = creating_word_wout_o(input, i, operators, lexer);
		i = calculating_end(input, i, operators);
	}
	i = null_terminator_check(input, i);
	return (word);
}
