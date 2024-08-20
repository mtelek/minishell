/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:24:38 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 20:34:25 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_redirections(t_lexer **temp_lex, t_cmd **temp_cmd)
{
	if ((*temp_lex)->type == INPUT_RED)
		(*temp_cmd)->n_in++;
	else if ((*temp_lex)->type == OUTPUT_RED)
		(*temp_cmd)->n_out++;
	else if ((*temp_lex)->type == APPEND_OUT)
		(*temp_cmd)->n_append++;
	else if ((*temp_lex)->type == HEREDOC)
	{
		(*temp_cmd)->n_heredoc++;
		(*temp_cmd)->hd_indicator = 1;
	}
	*temp_lex = (*temp_lex)->next;
}

void	assign_argument(t_lexer **temp_lex, t_cmd **temp_cmd, int i)
{
	if (i > 0 && (*temp_lex) && (*temp_lex)->prev->type != OUTPUT_RED
		&& (*temp_lex)->prev->type != HEREDOC
		&& (*temp_lex)->prev->type != APPEND_OUT)
	{
		(*temp_cmd)->args[i] = (*temp_lex)->str;
	}
	else if (i == 0 && (*temp_lex))
	{
		(*temp_cmd)->args[i] = (*temp_lex)->str;
	}
}

int	setting_args(t_lexer **temp_lex, t_cmd **temp_cmd, int n_args)
{
	int	i;

	i = 0;
	while ((*temp_lex) != NULL && (*temp_lex)->type != PIPE)
	{
		if (i < n_args)
		{
			if ((*temp_lex)->type >= INPUT_RED
				&& (*temp_lex)->type <= APPEND_OUT)
				handle_redirections(temp_lex, temp_cmd);
			else
				assign_argument(temp_lex, temp_cmd, i);
			i++;
		}
		if (*temp_lex)
			(*temp_lex) = (*temp_lex)->next;
	}
	return (i);
}

int	count_cmds(t_lexer *lexer)
{
	int	n_cmds;

	n_cmds = 0;
	if (lexer)
		n_cmds++;
	if (lexer->type != 6 && lexer->next && !lexer->next->next)
		n_cmds--;
	while (lexer != NULL && lexer->next != NULL)
	{
		if (lexer->type == 1 && lexer->next->type == 6)
			n_cmds++;
		lexer = lexer->next;
	}
	return (n_cmds);
}

int	number_of_args(t_lexer *lexer)
{
	int				count;
	static t_lexer	*temp;
	static int		k;
	int				n_cmds;

	n_cmds = count_cmds(lexer);
	count = 0;
	if (temp == NULL)
		temp = lexer;
	while (temp != NULL && temp->type != 1)
	{
		count++;
		temp = temp->next;
	}
	if (temp != NULL && temp->type == 1)
		temp = temp->next;
	k++;
	if (k == n_cmds)
	{
		temp = NULL;
		k = 0;
	}
	return (count);
}
