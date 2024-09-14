/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:22 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/08 10:05:32 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	fork_failed(t_main *main)
{
	if (errno == EAGAIN)
		ft_putstr_fd(E_LIMIT_INSUF, 2);
	else if (errno == ENOMEM)
		ft_putstr_fd(E_INSUF_MEM, 2);
	else
		ft_putstr_fd(E_CREATING_PROCESS, 2);
	free_structs(main);
	exit (EXIT_FAILURE);
}

void	pipe_failed(t_main *main)
{
	if (errno == EFAULT)
		ft_putstr_fd(E_INVALID_FD_PIPE, 2);
	else if (errno == EMFILE)
		ft_putstr_fd(E_TOO_MANY_FD, 2);
	else if (errno == ENFILE)
		ft_putstr_fd(E_TOO_MANY_FILES, 2);
	else
		ft_putstr_fd(E_PIPE_CREATION, 2);
	free_structs(main);
	exit (EXIT_FAILURE);
}

void	readdir_failed(t_main *main, DIR *dir)
{
	if (errno == EBADF)
		ft_putstrs_fd(E_INV_D_STREAM, (void *)dir, "\n", 2);
	else
	{
		ft_putstrs_fd(E_READ_DIR, (void *)dir, "\n", 2);
		ft_putstr_fd("\n", 2);
	}
	free_structs(main);
	exit (EXIT_FAILURE);
}

void	closedir_failed(t_main *main, DIR *dir)
{
	if (errno == EBADF)
		ft_putstrs_fd(E_INV_D_STREAM, (void *)dir, "\n", 2);
	else
	{
		ft_putstrs_fd(E_CLOSE_DIR, (void *)dir, "\n", 2);
		ft_putstr_fd("\n", 2);
	}
	free_structs(main);
	exit (EXIT_FAILURE);
}
