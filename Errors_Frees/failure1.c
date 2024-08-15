/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:22 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 22:31:53 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	fork_failed(t_main *main)
{
	if (errno == EAGAIN)
		printf(E_LIMIT_INSUF);
	else if (errno == ENOMEM)
		printf(E_INSUF_MEM);
	else
		printf(E_CREATING_PROCESS, strerror(errno));
	free_structs(main);
	perror("");
	exit(EXIT_FAILURE);
}

void	pipe_failed(t_main *main)
{
	if (errno == EFAULT)
		printf(E_INVALID_FD_PIPE);
	else if (errno == EMFILE)
		printf(E_TOO_MANY_FD);
	else if (errno == ENFILE)
		printf(E_TOO_MANY_FILES);
	else
		printf(E_PIPE_CREATION, strerror(errno));
	free_structs(main);
	perror("");
	exit(EXIT_FAILURE);
}

void	readdir_failed(t_main *main, DIR *dir)
{
	if (errno == EBADF)
		printf(E_INV_D_STREAM, (void *)dir);
	else
		printf(E_READ_DIR, (void *)dir, strerror(errno));
	free_structs(main);
	perror("");
	exit(EXIT_FAILURE); // might not be necessary here
}

void	closedir_failed(t_main *main, DIR *dir)
{
	if (errno == EBADF)
		printf(E_INV_D_STREAM, (void *)dir);
	else
		printf(E_CLOSE_DIR, (void *)dir, strerror(errno));
	free_structs(main);
	perror("");
	exit(EXIT_FAILURE); // might not be necessary here
}
