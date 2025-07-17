/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:03:45 by mtelek            #+#    #+#             */
/*   Updated: 2025/07/17 15:28:56 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	error_message(int exit_code, char *message, char *path, t_main *main)
{
	ft_putstrs_fd(NULL, path, message, STDERR_FILENO);
	free_structs(main);
	exit(exit_code);
}

void	execve_error(t_main *main, char *path)
{
	DIR		*dir;
	int		fd;
	int		close_result;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	if (!ft_strchr(path, '/'))
		error_message(127, NO_CMD, path, main);
	else if (fd == -1)
	{
		if (dir)
			error_message(126, IS_DIR, path, main);
		else
			error_message(127, NO_DIR, path, main);
	}
	else
		error_message(126, NO_PERMISSION, path, main);
	if (dir)
	{
		close_result = closedir(dir);
		if (close_result == -1)
			closedir_failed(main, 0);
	}
	if (close(fd) == -1)
		close_failed(main, fd);
}

void	error_type10(int error_type)
{
	if (error_type == -1)
		ft_putstr_fd(ERROR_STRDUP, STDERR_FILENO);
	else if (error_type == 0)
		ft_putstr_fd(MF_ENV_LIST, STDERR_FILENO);
	else if (error_type == 1)
		ft_putstr_fd(MF_OPERATOR, STDERR_FILENO);
	else if (error_type == 2)
		ft_putstr_fd(MF_LEXER, STDERR_FILENO);
	else if (error_type == 3)
		ft_putstr_fd(MF_WORD, STDERR_FILENO);
	else if (error_type == 4)
		ft_putstr_fd(MF_CMD_TABLE, STDERR_FILENO);
	else if (error_type == 5)
		ft_putstr_fd(MF_CMD_ARGS, STDERR_FILENO);
	else if (error_type == 6)
		ft_putstr_fd(MF_CMD_CMD, STDERR_FILENO);
	else if (error_type == 7)
		ft_putstr_fd(MF_PARSER, STDERR_FILENO);
	else if (error_type == 8)
		ft_putstr_fd(MF_PIPES, STDERR_FILENO);
	else if (error_type == 9)
		ft_putstr_fd(MF_ONE_PIPE, STDERR_FILENO);
}

void	error_type20(int error_type)
{
	if (error_type == 10)
		ft_putstr_fd(MF_N_ENV_ARRAY, STDERR_FILENO);
	else if (error_type == 11)
		ft_putstr_fd(MF_HEREDOC, STDERR_FILENO);
	else if (error_type == 12)
		ft_putstr_fd(MF_BUILTIN, STDERR_FILENO);
	else if (error_type == 13)
		ft_putstr_fd(MF_INPUT_FD, STDERR_FILENO);
	else if (error_type == 14)
		ft_putstr_fd(MF_EXEC, 2);
	else if (error_type == 15)
		ft_putstr_fd(MF_OUPUT_FD, STDERR_FILENO);
	if (error_type == 16)
		ft_putstr_fd(MF_APPEND_OUT, 2);
	else if (error_type == 18)
		ft_putstr_fd(MF_ENV_ARRAY, 2);
	else if (error_type == 19)
		ft_putstr_fd(ERROR_STRDUP, 2);
	else if (error_type == 20)
		ft_putstr_fd(MF_STRJOIN, 2);
}

void	error_type30(int error_type)
{
	if (error_type == 21)
		ft_putstr_fd(MF_STRTRIM, 2);
	else if (error_type == 22)
		ft_putstr_fd(MF_SUBSTR, 2);
	else if (error_type == 23)
		ft_putstr_fd(MF_STRING, 2);
	else if (error_type == 24)
		ft_putstr_fd(MF_NEW_STR, 2);
	else if (error_type == 25)
		ft_putstr_fd(MF_EXPNAD_NODE, 2);
	else if (error_type == 26)
		ft_putstr_fd(MF_DELIMITER, 2);
	else if (error_type == 27)
		ft_putstr_fd(MF_CD_ARGV, 2);
	else if (error_type == 28)
		ft_putstr_fd(MF_T_CD, 2);
	else if (error_type == 29)
		ft_putstr_fd(MF_REALLOC, 2);
}
