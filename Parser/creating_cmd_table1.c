/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:18:16 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/03 15:20:25 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	setting_args(t_lexer **temp_lex, t_cmd **temp_cmd, int n_args)
{
	int	i;

	i = 0;
	while ((*temp_lex) != NULL && (*temp_lex)->type != 1)
	{
		if ((*temp_lex)->type != 6 && (*temp_lex)->next
			&& (*temp_lex)->next->next)
			(*temp_lex) = (*temp_lex)->next->next;
		else if ((*temp_lex)->type != 6 && !(*temp_lex)->next->next)
			break ;
		else
		{
			if (i < n_args)
			{
				(*temp_cmd)->args[i] = (*temp_lex)->str;
				i++;
			}
			(*temp_lex) = (*temp_lex)->next;
		}
	}
	return (i);
}

void	args_maker(t_lexer *lexer, t_cmd *cmd, int n_cmds, int n_args)
{
	int				i;
	static int		k;
	static t_lexer	*temp_lex;
	static t_cmd	*temp_cmd;

	if (temp_cmd == NULL)
		temp_cmd = cmd;
	if (temp_lex == NULL)
		temp_lex = lexer;
	i = setting_args(&temp_lex, &temp_cmd, n_args);
	cmd->args[i] = NULL;
	if (temp_lex != NULL)
		temp_lex = temp_lex->next;
	temp_cmd = temp_cmd->next;
	k++;
	if (k == n_cmds)
	{
		temp_cmd = NULL;
		temp_lex = NULL;
		k = 0;
	}
}

void	init_node(t_main *main, t_cmd **cmd, t_cmd **prev_node, int n_cmds)
{
	t_cmd	*temp;
	int		j;
	int		n_args;

	j = 0;
	n_args = number_of_args(main->lexer);
	temp = malloc(sizeof(t_cmd));
	if (!temp)
		error_function(4, main->operators, main->lexer, *cmd);
	temp->args = malloc(sizeof(char *) * (n_args + 1));
	if (!temp->args)
		error_function(5, main->operators, main->lexer, *cmd);
	while (j < n_args)
		temp->args[j++] = NULL;
	temp->next = NULL;
	args_maker(main->lexer, temp, n_cmds, n_args);
	temp->cmd = ft_strdup(temp->args[0]);
	if (!temp->cmd)
		error_function(6, main->operators, main->lexer, *cmd);
	temp->prev = *prev_node;
	if (*prev_node)
		(*prev_node)->next = temp;
	else
		*cmd = temp;
	*prev_node = temp;
}

void	creating_cmd_table(t_main *main)
{
	t_cmd	*prev_node;
	int		n_cmds;
	int		i;

	i = 0;
	prev_node = NULL;
	n_cmds = count_cmds(main->lexer);
	if (!n_cmds)
		return ;
	while (i < n_cmds)
	{
		init_node(main, &main->cmd, &prev_node, n_cmds);
		i++;
	}
}
