/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:24:38 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/04 23:32:04 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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
	else if (i == 1 && ((*temp_lex)->prev->type == HEREDOC
			|| (*temp_lex)->prev->type == APPEND_OUT
			|| (*temp_lex)->prev->type == INPUT_RED
			|| (*temp_lex)->prev->type == OUTPUT_RED))
		(*temp_cmd)->args[i] = (*temp_lex)->str;
}

int	setting_args(t_lexer **temp_lex, t_cmd **temp_cmd, int n_args, t_main *main)
{
	int	i;

	i = 0;
	init_variables(temp_cmd);
	while ((*temp_lex) != NULL && (*temp_lex)->type != PIPE)
	{
		if (i < n_args)
		{
			if ((*temp_lex)->type >= INPUT_RED
				&& (*temp_lex)->type <= APPEND_OUT)
				handle_redirections(temp_lex, temp_cmd, i, main);
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
	while (lexer != NULL && lexer->next != NULL)
	{
		if (lexer->type == 1)
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
