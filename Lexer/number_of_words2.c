/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_words2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:38:11 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/28 00:14:04 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	ops_check(char *input, int i)
{
	if ((input[i] != '|' && input[i + 1] == '|')
		|| (input[i] != '<' && input[i + 1] == '<')
		|| (input[i] != '>' && input[i + 1] == '>'))
		return (1);
	if (input[i] && input[i + 1]
		&& (input[i] == '<' || input[i] == '>')
		&& !ft_isspace(input[i + 1])
		&& (input[i + 1] != '>' && input[i + 1] != '<'
			&& input[i + 1] != '|'))
		return (1);
	return (0);
}

int	checking_for_doubles(char *input, int i)
{
	if (input[i] && input[i + 1])
	{
		if ((input[i + 1] == '<' && input[i] == '<')
			|| (input[i + 1] == '>' && input[i] == '>')
			|| (input[i + 1] == '|' && input[i] == '|'))
		{
			i++;
		}
		i++;
	}
	return (i);
}

int	op_check(char *op, t_operator *operators)
{
	int	op_len;

	op_len = ft_strlen(op);
	while (operators != NULL && op)
	{
		if (!ft_strncmp(op, operators->operator, op_len))
		{
			free(op);
			return (1);
		}
		operators = operators->next;
	}
	free(op);
	return (0);
}

int	is_operator(char c1, char c2, t_operator *operators, t_main *main)
{
	char	*op;

	if (((c1 == 124 && c2 == 124) || (c1 == 60 && c2 == 60) || (c1 == 62
				&& c2 == 62)))
	{
		op = malloc(3);
		if (!op)
			error_function(2, main);
		op[0] = c1;
		op[1] = c2;
		op[2] = '\0';
	}
	else
	{
		op = malloc(2);
		if (!op)
			error_function(2, main);
		op[0] = c1;
		op[1] = '\0';
	}
	if (op_check(op, operators))
		return (1);
	return (0);
}
