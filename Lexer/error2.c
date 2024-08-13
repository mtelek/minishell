/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:03:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/13 00:14:06 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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
	else if (error_type == 10)
		ft_putstr_fd(ERROR_PIPE, 2);
}

int execve_error(char *path)
{
	DIR		*dir;
	int		fd;
	int		exit_code;

	fd = open(path, O_WRONLY); //can fail
	dir = opendir(path); //can fail
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
		closedir(dir); //error menagement, can fail
	close(fd); //error menagement, can fail
	return (exit_code);
}

void	exec_error_function(t_main *main, char *path)
{
	int exit_code;

	exit_code = 0;
	exit_code = execve_error(path);
	error_function(20, main);
	exit(exit_code);
}

void	error_type20(int error_type)
{
	if (error_type == 11)
		ft_putstr_fd(ERROR_FORK, 2);
	else if (error_type == 12)
		ft_putstr_fd(ERROR_DUP2, 2);
	else if (error_type == 13)
		ft_putstr_fd(MF_INPUT_FD, 2);
	else if (error_type == 14)
		ft_putstr_fd(ERROR_OPEN, 2);
	else if (error_type == 15)
		ft_putstr_fd(MF_OUPUT_FD, 2);
	else if (error_type == 16)
		ft_putstr_fd(MF_APPEND_OUT, 2);
	else if (error_type == 17)
		ft_putstr_fd(ERROR_CLOSE, 2);
	else if (error_type == 18)
		ft_putstr_fd(MF_ENV_ARRAY, 2);
	else if (error_type == 19)
		ft_putstr_fd(ERROR_STRDUP, 2);
}
