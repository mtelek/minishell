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

int		g_parent_exit = 0;

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

void	check_for_spaces(t_main *main, t_lexer *lexer)
{
	t_lexer	*temp;

	temp = lexer;
	while (lexer != NULL)
	{
		if ((lexer == temp || (lexer->prev && lexer->prev->type == PIPE))
			&& find_character(lexer->str, ' ') != -1
			&& !is_only_spaces(lexer->str))
		{
			split_and_insert_lexer_nodes(lexer, main);
		}
		lexer = lexer->next;
	}
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
	check_for_spaces(main, main->lexer);
	parser(main);
	setup_parent_signal_handlers();
	main->heredoc_flag = 0;
	ok_free_function(main);
	return ;
}

void	input_set_up(t_main *main, char *input, int *m_exit_code)
{
	main->count_line += 1;
	(*m_exit_code) = 0;
	if (*input != '\0' && !is_only_spaces(input))
		add_history(input);
	minishell(input, main);
	free(input);
	(*m_exit_code) = main->exit_code;
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	char	*input;
	int		m_exit_code;

	m_exit_code = 0;
	init_main(&main);
	creating_env_array(&main, envp);
	argc_checker(argc, argv);
	setup_parent_signal_handlers();
	while (1)
	{
		if (!main.heredoc_flag)
		{
			input = readline("minishell> ");
			if (g_parent_exit)
				update_global(&main);
			if (input)
				input_set_up(&main, input, &m_exit_code);
			else if (input == NULL)
				return (clear_history(), free_main(&main),
					free(input), m_exit_code);
		}
	}
	return (m_exit_code);
}
