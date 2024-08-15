/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:03:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 22:53:34 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	execve_error(t_main *main, char *path)
{
	DIR		*dir;
	int		fd;
	int		exit_code;

	fd = open(path, O_WRONLY);
	if (fd == -1)
		open_failed(main, path);
	dir = opendir(path);
	ft_putstr_fd("minishell> ", 2);
	ft_putstr_fd(path, 2);
	if (!ft_strchr(path, '/'))
	{
		ft_putstr_fd(": command not found\n", 2);
		exit_code = 127;
	}
	else if (fd == -1)
	{
		if (dir)
		{
			ft_putstr_fd(": is a directory\n", 2);
			exit_code = 126;
		}
		else
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			exit_code = 127;
		}
	}
	else
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit_code = 126;
	}
	if (dir)
		if (closedir(dir) == -1)
			closedir_failed(main, dir);
	if (close(fd) == -1)
		close_failed(main, fd);
	return (exit_code);
}

void	error_type10(int error_type)
{
	if (error_type == -1)
		ft_putstr_fd(ERROR_STRDUP, 2);
	else if (error_type == 0)
		ft_putstr_fd(MF_ENV_LIST, 2);
	else if (error_type == 1)
		ft_putstr_fd(MF_OPERATOR, 2);
	else if (error_type == 2)
		ft_putstr_fd(MF_LEXER, 2);
	else if (error_type == 3)
		ft_putstr_fd(MF_WORD, 2);
	else if (error_type == 4)
		ft_putstr_fd(MF_CMD_TABLE, 2);
	else if (error_type == 5)
		ft_putstr_fd(MF_CMD_ARGS, 2);
	else if (error_type == 6)
		ft_putstr_fd(MF_CMD_CMD, 2);
	else if (error_type == 7)
		ft_putstr_fd(MF_PARSER, 2);
	else if (error_type == 8)
		ft_putstr_fd(MF_PIPES, 2);
	else if (error_type == 9)
		ft_putstr_fd(MF_ONE_PIPE, 2);
}

void	error_type20(int error_type)
{
	if (error_type == 13)
		ft_putstr_fd(MF_INPUT_FD, 2);
	else if (error_type == 15)
		ft_putstr_fd(MF_OUPUT_FD, 2);
	else if (error_type == 16)
		ft_putstr_fd(MF_APPEND_OUT, 2);
	else if (error_type == 18)
		ft_putstr_fd(MF_ENV_ARRAY, 2);
	else if (error_type == 19)
		ft_putstr_fd(ERROR_STRDUP, 2);
}
