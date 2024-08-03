/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:04:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/03 20:11:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

//! quotes removal not working correctly if "hgfg'fg'"

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

void	delete_qoutes(t_lexer *lexer)
{
	int	start;
	int	end;
	int	temp_start;

	while (lexer != NULL)
	{
		temp_start = qoutes_checker(lexer->str, 34, -1);
		start = qoutes_checker(lexer->str, 39, -1);
		if ((temp_start != 0 && temp_start < start) || start == 0)
			start = temp_start;
		if (lexer->str[start])
			end = qoutes_handler(lexer->str, start) - 1;
		if (end != 0)
			remove_quotes(lexer->str, start, end);
		lexer = lexer->next;
	}
}
