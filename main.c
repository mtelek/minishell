/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:34 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/28 22:05:16 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/minishell.h"

void remove_quotes(char *str, int start, int end)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != str[start])
		i++;
	while (str[i] != '\0' && str[i+1] != str[end])
	{
		str[i] = str[i+1];
		i++;
	}
	str[i] = '\0';
	return;
}

void	delete_qoutes(t_lexer *lexer)
{
	int start;
	int end;
	int temp_start;

	while (lexer != NULL)
	{
		temp_start = qoutes_checker(lexer->str, 34, -1); //not working for " if its not at the first place
			start = qoutes_checker(lexer->str, 39, -1);
		if (temp_start < start)
			start = temp_start;
		if (lexer->str[start])
			end = qoutes_handler(lexer->str, start) - 1;
		printf("Start:%d\n", start);
		printf("End:%d\n", end);
		if (end == 0 && start == 0)
		 	return;
		remove_quotes(lexer->str, start, end);
		lexer = lexer->next;
	}
}

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
	delete_qoutes(lexer);
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
