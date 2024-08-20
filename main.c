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
	int			j;
	t_cmd		*temp_cmd;

	temp_cmd = cmd;
	while (temp_cmd != NULL)
	{
		j = 0;
		printf("NEW_CMD_TABLE\n");
		printf("IN_FD:%d\n", temp_cmd->in_fd);
		printf("OUT_FD:%d\n", temp_cmd->out_fd);
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

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	init_main(t_main *main)
{
	main->env_array = NULL;
	main->operators = NULL;
	main->lexer = NULL;
	main->cmd = NULL;
	main->parser = NULL;
	main->exec = NULL;
	main->builtin = NULL;
	main->exit_code = 0;
	main->hd_content = NULL;
	main->heredoc_flag = 0;
	main->printf_flag = 0;
}

int	minishell(char *input, t_main *main)
{
	init_operators(&main->operators, main);
	if (get_tokens(input, &main->lexer, main) == -1)
		return (free_operator(main->operators), 0);
	if (!syntax_check(main->lexer, main))
	{
		ok_free_function(main);
		main->exit_code = 2;
		exit(main->exit_code);
	}
	delete_qoutes(main->lexer);
	parser(main);
	main->heredoc_flag = 0;
	ok_free_function(main);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	char	*input;
	char	*history_file;

	init_main(&main);
	creating_env_array(&main, envp);
	history_file = ".minishell_history";
	read_history(history_file);
	argc_checker(argc, argv);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (!main.heredoc_flag)
		{
			if (isatty(fileno(stdin)))
				input = readline("tester> ");
			else
			{
				char	*line;
				line = get_next_line(fileno(stdin));
				if (!line)
					input = ft_strtrim(line, "\n");
				else
					input = NULL;
				free(line);
			}
			if (!input)
			{
				if (isatty(fileno(stdin)))
					printf("exit\n");
				ok_free_function(&main);
				exit (main.exit_code);
			}
			minishell(input, &main);
			free(input);
			// input = readline("minishell> ");
			// if (input)
			// {
			// 	if (*input != '\0')
			// 		add_history(input);
			// 	minishell(input, &main);
			// }
			// else
			// {
			// 	write_history(history_file);
			// 	return (write(1, "exit\n", 5), free(input), 0);
			// }
			// free(input);
		}
	}
	//clear_history();
	return (0);
}
