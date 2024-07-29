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

int	op_check(char *op, t_operator *operators)
{
	while (operators != NULL)
	{
		if (!ft_strncmp(op, operators->operator, 2))
		{
			free(op);
			return (1);
		}
		operators = operators->next;
	}
	return (0);
}

char	setting_c2(char c2)
{
	if (!c2)
	{
		c2 = 0;
		return (c2);
	}
	return (c2);
}

int	is_operator(char c1, char c2, t_operator *operators)
{
	char	*op;

	setting_c2(c2);
	if ((c1 == 124 && c2 == 124) || (c1 == 60 && c2 == 60) || (c1 == 62
			&& c2 == 62))
	{
		op = malloc(3);
		if (!op)
			error_function(2, operators, NULL);
		op[0] = c1;
		op[1] = c2;
		op[2] = '\0';
	}
	else
	{
		op = malloc(2);
		if (!op)
			error_function(2, operators, NULL);
		op[0] = c1;
		op[1] = '\0';
	}
	if (op_check(op, operators))
		return (1);
	free(op);
	return (0);
}
