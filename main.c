/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/16 16:31:34 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/28 22:05:16 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers/minishell.h"

void	print_cmd_table(t_cmd *cmd)
{
	int		j;
	t_cmd	*temp_cmd;

	temp_cmd = cmd;
	while (temp_cmd != NULL)
	{
		j = 0;
		printf("NEW_CMD_TABLE\n");
		while (temp_cmd->args[j])
		{
			printf("ARGS: %s\n", temp_cmd->args[j]);
			j++;
		}
		temp_cmd = temp_cmd->next;
	}
}

void	print_lexer(t_lexer *lexer)
{
	t_lexer	*temp_lex;

	temp_lex = lexer;
	printf("LEXER\n");
	while (temp_lex != NULL)
	{
		printf("Tokens:%s\n", temp_lex->str);
		temp_lex = temp_lex->next;
	}
}

int	minishell(char *input)
{
	t_main		main;

	main.operators = NULL;
	main.lexer = NULL;
	main.cmd = NULL;
	init_operators(&main.operators);
	if (get_tokens(input, main.operators, &main.lexer) == -1)
		return (error_operators(main.operators), 0);
	print_lexer(main.lexer);
	if (syntax_check(main.operators, main.lexer) == false)
	{
		ok_free_function(main.operators, main.lexer, NULL);
		exit(2);
	}
	delete_qoutes(main.lexer);
	creating_cmd_table(&main);
	print_cmd_table(main.cmd);
	ok_free_function(main.operators, main.lexer, main.cmd);
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
		input = NULL;
		free(input);
		input = readline("minishell> ");
		if (input)
		{
			minishell(input);
			free(input);
		}
	}
	return (0);
}
