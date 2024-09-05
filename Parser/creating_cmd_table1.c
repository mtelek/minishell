/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:18:16 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 23:55:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	args_maker(t_cmd *cmd, int n_cmds, int n_args, t_main *main)
{
	int				i;
	static int		k;
	static t_lexer	*temp_lex;
	static t_cmd	*temp_cmd;

	cmd->n_in = 0;
	cmd->n_out = 0;
	cmd->n_append = 0;
	cmd->n_heredoc = 0;
	if (temp_cmd == NULL)
		temp_cmd = cmd;
	if (temp_lex == NULL)
		temp_lex = main->lexer;
	i = setting_args(&temp_lex, &temp_cmd, n_args, main);
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

void	init_variables(t_cmd **temp)
{
	(*temp)->in = NULL;
	(*temp)->out = NULL;
	(*temp)->append = NULL;
	(*temp)->delimiter = NULL;
}

void	init_cmd_fd(t_main *main, t_cmd *temp, t_cmd **cmd)
{
	(void)cmd;
	temp->true_command = false;
	if (temp->args[0] && !is_operator(temp->args[0][0],
		temp->args[0][1], main->operators, main))
	{
		temp->cmd = temp->args[0];
		if (!temp->cmd)
			error_function(6, main);
	}
	else
	{
		temp->cmd = ft_strdup("true");
		if (!temp->cmd)
			error_function(6, main);
		temp->true_command = true;
	}
	temp->in_fd = STDIN_FILENO;
	temp->out_fd = STDOUT_FILENO;
	temp->pid = -1;
	temp->hd_content = NULL;
	temp->expander_decider = true;
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
		error_function(4, main);
	temp->args = malloc(sizeof(char *) * (n_args + 1));
	if (!temp->args)
		error_function(5, main);
	while (j < n_args)
		temp->args[j++] = NULL;
	temp->next = NULL;
	temp->hd_indicator = 0;
	temp->main = main;
	args_maker(temp, n_cmds, n_args, main);
	init_cmd_fd(main, temp, cmd);
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
