/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:19 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/21 16:43:22 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	close_failed(t_main *main, int fd)
{
	if (errno == EBADF)
		ft_putstr_fd(E_INV_FD_CLOSE, fd, main);
	else if (errno == EINTR)
		ft_putstr_fd(E_INT_SIG, fd, main);
	else
		ft_putstrs_fd(E_CLOSE_FD, strerror(errno), NULL, fd, main);
	free_structs(main);
}

void	dup_failed(t_main *main, int old_fd, int new_fd)
{
	if (errno == EBADF)
		ft_putstrs_fd(E_INV_FD, ft_itoa(old_fd), ft_itoa(new_fd), 2, main);
	else if (errno == EINTR)
		ft_putstrs_fd(E_DUP_SIG, ft_itoa(old_fd), ft_itoa(new_fd), 2, main);
	else if (errno == EMFILE)
		ft_putstrs_fd(E_TOO_MANY_FD_O, ft_itoa(old_fd), ft_itoa(new_fd), 2, main);
	else
	{
		ft_putstrs_fd(E_DUP_FD, ft_itoa(old_fd), ft_itoa(new_fd), 2, main);
		ft_putstr_fd(strerror(errno), 2, main);
	}
	free_structs(main);
}

void	open_failed(t_main *main, char *file_name)
{
	if (errno == EACCES)
		ft_putstrs_fd(E_PERMISSION_D_OPEN, file_name, NULL, 2, main);
	else if (errno == ENOENT)
		ft_putstrs_fd(E_NO_FILE, file_name, NULL, 2, main);
	else if (errno == EROFS)
		ft_putstrs_fd(E_READ_ONLY, file_name, NULL, 2, main);
	else
		ft_putstrs_fd(E_OPEN_FILE, file_name, strerror(errno), 2, main);
	free_structs(main);
}
