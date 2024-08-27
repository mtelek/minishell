/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:04:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/27 16:05:00 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	remove_quotes(char *str, int start, int end)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != str[start])
		i++;
	while (str[i + 1] != '\0' && str[i + 1] != str[end])
	{
		str[i] = str[i + 1];
		i++;
	}
	while (str[i + 2] != '\0')
	{
		str[i] = str[i + 2];
		i++;
	}
	str[i] = '\0';
	return ;
}

int	delete_qoutes(t_lexer *lexer, t_main *main)
{
	int	start;
	int	end;
	int	s_double;
	int	s_single;

	while (lexer != NULL)
	{
		if (ft_strcmp(lexer->str, "echo") == 0 && ft_strcmp(lexer->next->str, "$?") == 0)
			return (0);
		if (decide_to_expand(lexer, main))
			return (1);
		if (main->quotes_removed == false)
		{
			start = 0;
			s_double = qoutes_checker(lexer->str, 34, -1);
			s_single = qoutes_checker(lexer->str, 39, -1);
			if ((s_double < s_single && s_double != 0) || lexer->str[0] == 34)
				start = s_double;
			else if ((s_single < s_double && s_single != 0)
				|| lexer->str[0] == 39)
				start = s_single;
			if (start != -1)
				end = qoutes_handler(lexer->str, start) - 1;
			if (end != 0)
				remove_quotes(lexer->str, start, end);
		}
		lexer = lexer->next;
		main->quotes_removed = false;
	}
	return (0);
}
