/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:04:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 02:09:01 by mtelek           ###   ########.fr       */
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

void	delete_qoutes(t_expand_node *current)
{
	int	start;
	int	end;
	int	s_double;
	int	s_single;

	start = 0;
	end = 0;
	s_double = qoutes_checker(current->str, 34, -1);
	s_single = qoutes_checker(current->str, 39, -1);
	if ((s_double < s_single && s_double != 0) || current->str[0] == 34)
		start = s_double;
	else if ((s_single < s_double && s_single != 0)
		|| current->str[0] == 39)
		start = s_single;
	if (start != -1)
		end = qoutes_handler(current->str, start) - 1;
	if (end != 0)
		remove_quotes(current->str, start, end);
}

void	quotes_and_expander(t_lexer *lexer, t_main *main)
{
	while (lexer != NULL)
	{
		if (lexer->prev && lexer->prev->type == HEREDOC && !check_for_another_heredoc(lexer))
		{
			if (lexer->next)
				lexer = lexer->next;
			else
				return ;
		}
		if (ft_strcmp(lexer->str, "echo") == 0 && lexer->next
			&& ft_strcmp(lexer->next->str, "$?") == 0)
			return ;
		decide_to_expand(lexer, main);
		lexer = lexer->next;
	}
}
