/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:45:40 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 00:10:39 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_builtin(t_builtin *builtin)
{
	int	i;

	if (builtin == NULL)
		return ;
	if (builtin->export)
	{
		i = 0;
		while (builtin->export[i])
		{
			free(builtin->export[i]);
			i++;
		}
		free(builtin->export);
	}
	free(builtin);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i++]);
	}
	free(array);
}

void	free_file_names(t_cmd *temp_cmd)
{
	if (temp_cmd->append)
		free(temp_cmd->append);
	if (temp_cmd->in)
		free(temp_cmd->in);
	if (temp_cmd->out)
		free(temp_cmd->out);
	if (temp_cmd->delimiter)
		free(temp_cmd->delimiter);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp_cmd;

	if (cmd == NULL)
		return ;
	while (cmd != NULL)
	{
		temp_cmd = cmd;
		cmd = cmd->next;
		if (temp_cmd->hd_content)
		{
			free(temp_cmd->hd_content);
			temp_cmd->hd_content = NULL;
		}
		if (temp_cmd->true_command == true)
		{
			free(temp_cmd->cmd);
			temp_cmd->cmd = NULL;
		}
		free_file_names(temp_cmd);
		free(temp_cmd->args);
		temp_cmd->args = NULL;
		free(temp_cmd);
		temp_cmd = NULL;
	}
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp_lexer;

	if (lexer == NULL)
		return ;
	while (lexer != NULL)
	{
		temp_lexer = lexer;
		lexer = lexer->next;
		free(temp_lexer->str);
		temp_lexer->str = NULL;
		free(temp_lexer);
		temp_lexer = NULL;
	}
}

void	free_operator(t_operator *operators)
{
	t_operator	*temp_operator;

	if (operators == NULL)
		return ;
	while (operators != NULL)
	{
		temp_operator = operators;
		operators = operators->next;
		free(temp_operator->operator);
		temp_operator->operator = NULL;
		free(temp_operator);
		temp_operator = NULL;
	}
}
