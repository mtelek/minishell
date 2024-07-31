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
	while (str[i+1] != '\0' && str[i+1] != str[end])
	{
		str[i] = str[i+1];
		i++;
	}
	while (str[i+2] != '\0')
	{
		str[i] = str[i+2];
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
		temp_start = qoutes_checker(lexer->str, 34, -1);
			start = qoutes_checker(lexer->str, 39, -1);
		if ((temp_start != 0 && temp_start < start) || start == 0)
			start = temp_start;
		if (lexer->str[start])
			end = qoutes_handler(lexer->str, start) - 1;
		if (end != 0)
			remove_quotes(lexer->str, start, end);
		lexer = lexer->next;
	}
}

int	minishell(char *input)
{
	t_operator	*operators;
	t_lexer		*lexer;
	t_lexer		*temp_lex;
	t_cmd		*cmd;

	operators = NULL;
	lexer = NULL;
	cmd = NULL;
	init_operators(&operators);
	get_tokens(input, operators, &lexer);
	temp_lex = lexer;
	if (syntax_check(operators, lexer) == false)
	{
		ok_free_function(operators, lexer);
		exit(2);
	}
	delete_qoutes(lexer);
	creating_cmd_table(lexer, &cmd);
	while (cmd != NULL)
    {
        int m = 0;
        while (cmd->args[m])
        {
            printf("ARGS: %s\n", cmd->args[m]);
            m++;
        }
        printf("Next table:\n");
        cmd = cmd->next;
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
