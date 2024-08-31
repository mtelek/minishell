/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:04:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 01:59:38 by mtelek           ###   ########.fr       */
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

int	check_for_another_heredoc(t_lexer *temp_lex)
{
	if (temp_lex && temp_lex->next)
		temp_lex = temp_lex->next;
	while (temp_lex != NULL && temp_lex->type != PIPE)
	{
		if (temp_lex->type == HEREDOC)
			return (1);
		temp_lex = temp_lex->next;
	}
	return (0);
}

int	not_alphabetical_check(t_lexer *lexer, int *flag)
{
	if (lexer->str[0] == '$' && lexer->str[1] && !ft_isalpha(lexer->str[1]))
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

void	quotes_and_expander(t_lexer *lexer, t_main *main)
{
	int	flag;

	while (lexer != NULL)
	{
		flag = 0;
		if (lexer->prev && lexer->prev->type == HEREDOC
			&& !check_for_another_heredoc(lexer))
		{
			if (lexer->next)
				lexer = lexer->next;
			else
				return ;
		}
		if (ft_strcmp(lexer->str, "echo") == 0 && lexer->next
			&& ft_strcmp(lexer->next->str, "$?") == 0)
			return ;
		if (not_alphabetical_check(lexer, &flag) == 1)
			lexer = lexer->next;
		if (!flag)
		{
			decide_to_expand(lexer, main);
			lexer = lexer->next;
		}
	}
}
