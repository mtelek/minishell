/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:24:38 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 02:17:03 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void delimiter_check(t_cmd **cmd, t_lexer *temp_lex)
{
	int len;

	if (temp_lex && temp_lex->str)
	{
		len = ft_strlen(temp_lex->str);
		if (len > 1 && temp_lex->str[0] == 39 && temp_lex->str[len] == 39)
			(*cmd)->expander_decider = false;
	}
}

int check_for_another_heredoc(t_lexer *temp_lex)
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


void	handle_redirections(t_lexer **temp_lex, t_cmd **temp_cmd, int i)
{
	if ((i == 0 && (*temp_lex)->type != 6 && (*temp_lex)->next)
		|| ((*temp_lex)->prev && (*temp_lex)->prev->type == 1
			&& (*temp_lex)->type != 6 && (*temp_lex)->next))
	{
		(*temp_cmd)->args[i] = ((*temp_lex)->str); // error message missing
	}
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
		if (!check_for_another_heredoc((*temp_lex)))
			delimiter_check(temp_cmd, *temp_lex);
	}
	if (i != 0)
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
	else if (i == 1 && ((*temp_lex)->prev->type == HEREDOC
			|| (*temp_lex)->prev->type == APPEND_OUT
			|| (*temp_lex)->prev->type == INPUT_RED
			|| (*temp_lex)->prev->type == OUTPUT_RED))
		(*temp_cmd)->args[i] = (*temp_lex)->str;
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
				handle_redirections(temp_lex, temp_cmd, i);
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
