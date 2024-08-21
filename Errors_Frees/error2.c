/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:03:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/21 16:45:04 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	error_message(t_main *main, int exit_code, char *message, char *path)
{
	ft_putstrs_fd("minishell> ", path, message, 2, main);
	exit(exit_code);
}

void	execve_error(t_main *main, char *path)
{
	DIR		*dir;
	int		fd;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	if (!ft_strchr(path, '/'))
		error_message(main, 127, NO_CMD, path);
	else if (fd == -1)
	{
		if (dir)
			error_message(main, 126, IS_DIR, path);
		else
			error_message(main, 127, NO_DIR, path);
	}
	else
		error_message(main, 126, NO_PERMISSION, path);
	if (dir)
		if (closedir(dir) == -1)
			closedir_failed(main, dir);
	if (close(fd) == -1)
		close_failed(main, fd);
}

void	error_type10(int error_type, t_main *main)
{
	if (error_type == -1)
		ft_putstr_fd(ERROR_STRDUP, 2, main);
	else if (error_type == 0)
		ft_putstr_fd(MF_ENV_LIST, 2, main);
	else if (error_type == 1)
		ft_putstr_fd(MF_OPERATOR, 2, main);
	else if (error_type == 2)
		ft_putstr_fd(MF_LEXER, 2, main);
	else if (error_type == 3)
		ft_putstr_fd(MF_WORD, 2, main);
	else if (error_type == 4)
		ft_putstr_fd(MF_CMD_TABLE, 2, main);
	else if (error_type == 5)
		ft_putstr_fd(MF_CMD_ARGS, 2, main);
	else if (error_type == 6)
		ft_putstr_fd(MF_CMD_CMD, 2, main);
	else if (error_type == 7)
		ft_putstr_fd(MF_PARSER, 2, main);
	else if (error_type == 8)
		ft_putstr_fd(MF_PIPES, 2, main);
	else if (error_type == 9)
		ft_putstr_fd(MF_ONE_PIPE, 2, main);
}

void	error_type20(int error_type, t_main *main)
{
	if (error_type == 10)
		ft_putstr_fd(MF_N_ENV_ARRAY, 2, main);
	else if (error_type == 11)
		ft_putstr_fd(MF_HEREDOC, 2, main);
	else if (error_type == 12)
		ft_putstr_fd(MF_BUILTIN, 2, main);
	else if (error_type == 13)
		ft_putstr_fd(MF_INPUT_FD, 2, main);
	else if (error_type == 14)
		ft_putstr_fd(MF_EXEC, 2, main);
	else if (error_type == 15)
		ft_putstr_fd(MF_OUPUT_FD, 2, main);
	else if (error_type == 16)
		ft_putstr_fd(MF_APPEND_OUT, 2, main);
	else if (error_type == 18)
		ft_putstr_fd(MF_ENV_ARRAY, 2, main);
	else if (error_type == 19)
		ft_putstr_fd(ERROR_STRDUP, 2, main);
}
