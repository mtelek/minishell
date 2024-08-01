/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:40:25 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:25:47 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void ok_free_function(t_operator *operators, t_lexer *lexer, t_cmd *cmd)
{
    int i;
	t_lexer *temp_lexer;
	t_operator *temp_operator;
	t_cmd *temp_cmd;

    while (lexer != NULL && lexer->prev != NULL) 
        lexer = lexer->prev;
    while (lexer != NULL)
    {
        temp_lexer = lexer;
        lexer = lexer->next;
        temp_lexer->str = NULL;
        free(temp_lexer->str);
        free(temp_lexer);
        temp_lexer = NULL;
    }
    while (operators != NULL && operators->prev != NULL)
        operators = operators->prev;
    while (operators != NULL)
    {
        temp_operator = operators;
        operators = operators->next;
        free(temp_operator->operator);
        temp_operator->operator = NULL;
        free(temp_operator);
        temp_operator = NULL;
    }
    while (cmd != NULL && cmd->prev != NULL)
        cmd = cmd->prev;
    while (cmd != NULL)
    {
        temp_cmd = cmd;
        cmd = cmd->next;
        i = 0;
        while (temp_cmd->args[i])
        {
            free(temp_cmd->args[i]);
            temp_cmd->args[i] = NULL;
            i++;
        }
		free(temp_cmd->args[i]);
        free(temp_cmd->args);
        temp_cmd->args = NULL;
        free(temp_cmd);
        temp_cmd = NULL;
    }
}


void	error_function(int error_type, t_operator *operators, t_lexer *lexer)
{
	while (operators != NULL)
	{
		free(operators->operator);
		free(operators);
		operators = operators->next;
	}
	if (error_type == 2 || error_type == 3)
	{
		while (lexer != NULL)
		{
			free(lexer->str);
			free(lexer);
			lexer = lexer->next;
		}
	}
	if (error_type == 1)
		ft_putstr_fd("Error, malloc for operators failed\n", 2);
	else if (error_type == 2)
		ft_putstr_fd("Error, malloc for lexer failed\n", 2);
	else if (error_type == 3)
		ft_putstr_fd("Error, malloc for creating the word failed\n", 2);
	exit(2);
}
