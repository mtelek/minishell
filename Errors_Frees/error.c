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
	free_structs(main);
}

void	free_structs(t_main *main)
{
	free_operator(main->operators);
	free_lexer(main->lexer);
	free_cmd(main->cmd);
	free_parser(main->parser);
	free_exec(main->exec);
}

void	error_function(int error_type, t_main *main)
{
	free_structs(main);
	if (error_type <= 10)
		error_type10(error_type, main);
	else if (error_type <= 20 && error_type > 10)
		error_type20(error_type, main);
	exit(1);
}
