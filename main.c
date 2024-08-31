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

void	print_expand(t_expand_node *expand)
{
	t_expand_node *temp_expand;

	temp_expand = expand;
	printf("EXPAND\n");
	while (temp_expand != NULL)
	{
		printf("EXPAND_STR: %s\n", temp_expand->str);
		temp_expand = temp_expand->next;
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
	main->heredoc_flag = 0;
	main->count_line = 0;
	main->count_hd_line = 0;
	main->quotes_removed = false;
}

void	minishell(char *input, t_main *main)
{
	init_operators(&main->operators, main);
	if (get_tokens(input, &main->lexer, main) == -1)
	{
		free_operator(main->operators);
		main->exit_code = 1;
		return ;
	}
	if (!syntax_check(main->lexer, main))
	{
		syntax_free(main);
		main->exit_code = 2;
		return ;
	}
	quotes_and_expander(main->lexer, main);
	parser(main);
	main->heredoc_flag = 0;
	ok_free_function(main);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	char	*input;
	char	*history_file;
	int		m_exit_code;

//heredoc malloc issues
// cd leaks.
// check for true command with <<
// ctrl c and d in heredoc
// export t=" -l"  -> ls$t does expand but not run the expanded version ls -l
//Yes, in many shells, including those that follow the POSIX standard or are similar to bash, variable expansion typically requires that the character
// following $ be a letter or underscore. This rule helps distinguish environment variables from other tokens and prevent ambiguity.
// add ? as var delimiter in expander:

	m_exit_code = 0;
	init_main(&main);
	creating_env_array(&main, envp);
	history_file = ".minishell_history";
	read_history(history_file);
	argc_checker(argc, argv);
	setup_parent_signal_handlers();
	while (1)
	{
		if (!main.heredoc_flag)
		{
			input = readline("minishell> ");
			if (input)
			{
				main.count_line += 1;
				m_exit_code = 0;
				if (*input != '\0')
					add_history(input);
				minishell(input, &main);
				free(input);
				m_exit_code = main.exit_code;
			}
			else if (input == NULL)
			{
				clear_history();
				free_main(&main);
				free(input);
				remove(history_file);
				return (m_exit_code);
			}
		}
	}
	return (m_exit_code);
}
