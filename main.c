/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:34 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:21:41 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/minishell.h"

int	minishell(char *input)
{
	t_operator	*operators;
	t_lexer		*lexer;
	t_lexer		*temp_lex;

	operators = NULL;
	lexer = NULL;
	init_operators(&operators);
	get_tokens(input, operators, &lexer);
	temp_lex = lexer;
	if (syntax_check(operators, lexer) == false)
	{
		ok_free_function(operators, lexer);
		exit(2);
	}
	while (temp_lex != NULL)
	{
		printf("words:%s\n", temp_lex->str);
		temp_lex = temp_lex->next;
	}
	ok_free_function(operators, lexer);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*input;

	(void)argc;
	(void)argv;
	argc_checker(argc, argv);
	while (1)
	{
		input = readline("minishell> ");
		if (input)
		{
			minishell(input);
			free(input);
		}
	}
	return (0);
}
