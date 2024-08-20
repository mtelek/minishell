/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:19 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 22:13:15 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	close_failed(t_main *main, int fd)
{
	if (errno == EBADF)
		printf(E_INV_FD_CLOSE, fd);
	else if (errno == EINTR)
		printf(E_INT_SIG, fd);
	else
		printf(E_CLOSE_FD, fd, strerror(errno));
	free_structs(main);
	// perror("");
	exit(EXIT_FAILURE);
}

void	dup_failed(t_main *main, int old_fd, int new_fd)
{
	if (errno == EBADF)
		printf(E_INV_FD, old_fd, new_fd);
	else if (errno == EINTR)
		printf(E_DUP_SIG, old_fd, new_fd);
	else if (errno == EMFILE)
		printf(E_TOO_MANY_FD_O, old_fd, new_fd);
	else
		printf(E_DUP_FD, old_fd, new_fd, strerror(errno));
	free_structs(main);
	// perror("");
	exit(EXIT_FAILURE);
}

void	open_failed(t_main *main, char *file_name)
{
	if (errno == EACCES)
		printf(E_PERMISSION_D_OPEN, file_name);
	else if (errno == ENOENT)
		printf(E_NO_FILE, file_name);
	else if (errno == EROFS)
		printf(E_READ_ONLY, file_name);
	else
		printf(E_OPEN_FILE, file_name, strerror(errno));
	free_structs(main);
	// perror("");
	exit(EXIT_FAILURE); // might not be necessary here
}
