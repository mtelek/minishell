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

void	ok_free_function(t_operator *operators, t_lexer *lexer)
{
	t_operator	*temp_op;
	t_lexer		*temp_lex;

	while (lexer != NULL)
	{
		temp_lex = lexer;
		lexer = lexer->next;
		free(temp_lex->str);
		free(temp_lex);
	}
	while (operators != NULL)
	{
		temp_op = operators;
		operators = operators->next;
		free(temp_op->operator);
		free(temp_op);
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
