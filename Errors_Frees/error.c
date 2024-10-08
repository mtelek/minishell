/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/08/02 19:52:41 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/02 19:52:41 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	exec_error_function(t_main *main, char *path)
{
	execve_error(main, path);
}

void	free_structs(t_main *main)
{
	if (main->operators)
		free_operator(main->operators);
	if (main->lexer)
		free_lexer(main->lexer);
	if (main->cmd)
		free_cmd(main->cmd);
	if (main->parser)
		free_parser(main->parser);
	if (main->exec)
		free_exec(main->exec);
	if (main->builtin)
		free_builtin(main->builtin);
}

void	error_function(int error_type, t_main *main)
{
	free_structs(main);
	free_env_array(main->env_array);
	if (error_type < 10)
		error_type10(error_type);
	if (error_type <= 20 && error_type >= 10)
		error_type20(error_type);
	if (error_type <= 30 && error_type >= 21)
		error_type30(error_type);
	exit(1);
}
