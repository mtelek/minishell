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
		printf("IN_FD:%d\n", temp_cmd->in_fd);
		printf("IN_FD:%d\n", temp_cmd->out_fd);
		while (temp_cmd->args[j])
		{
			if (j == 0)
				printf("CMD:%s\n", temp_cmd->cmd);
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

int	minishell(char *input, char **envp)
{
	t_main		main;

	main.operators = NULL;
	main.lexer = NULL;
	main.cmd = NULL;
	main.env = envp;
	init_operators(&main.operators, &main);
	if (get_tokens(input, &main.lexer, &main) == -1)
		return (error_operators(main.operators), 0);
	// print_lexer(main.lexer);
	if (syntax_check(main.lexer) == false)
	{
		ok_free_function(main.operators, main.lexer, NULL);
		exit(2);
	}
	delete_qoutes(main.lexer);
	parser(&main);
	ok_free_function(main.operators, main.lexer, main.cmd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*history_file;

	//put env into linked list
	//one task, check errors if im freeing correctly
	//check ctrl d and c with valgrind
	//output file and append might not work with a pipe
	history_file = ".minishell_history";
	read_history(history_file);
	argc_checker(argc, argv);
	signal (SIGINT, handle_sigint);
	signal (SIGQUIT, SIG_IGN);
	while (1)
	{
		input = NULL;
		free(input);
		input = readline("minishell> ");
		if (input)
		{
			if (ft_strcmp(input, "history reset") == 0)
				clear_history();
			else if (*input != '\0')
				add_history(input);
			minishell(input, envp);
			free(input);
		}
		if (!input)
		{
			write_history(history_file);
			return (write(1, "exit\n", 5), free(input), 0);
		}
	}
	return (0);
}
