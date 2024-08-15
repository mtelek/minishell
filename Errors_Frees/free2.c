/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:45:40 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 22:47:04 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp_cmd;

	while (cmd != NULL)
	{
		temp_cmd = cmd;
		cmd = cmd->next;
		free(temp_cmd->args);
		temp_cmd->args = NULL;
		free(temp_cmd->cmd);
		temp_cmd->cmd = NULL;
		free(temp_cmd);
		temp_cmd = NULL;
	}
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp_lexer;

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

void	free_env_list(t_env *env)
{
	t_env	*temp_env;

	while (env != NULL)
	{
		temp_env = env;
		env = env->next;
		free(temp_env->env);
		temp_env->env = NULL;
		free(temp_env);
		temp_env = NULL;
	}
}
