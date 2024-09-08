/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:19 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/08 10:06:53 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	close_failed(t_main *main, int fd)
{
	if (errno == EBADF)
		ft_putstr_fd(E_INV_FD_CLOSE, fd);
	else if (errno == EINTR)
		ft_putstr_fd(E_INT_SIG, fd);
	else
		ft_putstrs_fd(E_CLOSE_FD, "\n", NULL, fd);
	free_structs(main);
	exit (EXIT_FAILURE);
}

void	dup_failed(t_main *main, int old_fd, int new_fd)
{
	if (errno == EBADF)
		ft_putstrs_fd(E_INV_FD, ft_itoa(old_fd), ft_itoa(new_fd), 2);
	else if (errno == EINTR)
		ft_putstrs_fd(E_DUP_SIG, ft_itoa(old_fd), ft_itoa(new_fd), 2);
	else if (errno == EMFILE)
		ft_putstrs_fd(E_TOO_MANY_FD_O, ft_itoa(old_fd), ft_itoa(new_fd), 2);
	else
		ft_putstrs_fd(E_DUP_FD, ft_itoa(old_fd), ft_itoa(new_fd), 2);
	ft_putstr_fd("\n", 2);
	free_structs(main);
	exit (EXIT_FAILURE);
}

void	open_failed(t_main *main, char *file_name)
{
	if (errno == EACCES)
		ft_putstrs_fd(E_PERMISSION_D_OPEN, file_name, "\n", 2);
	else if (errno == ENOENT)
		ft_putstrs_fd("bash: ", file_name, NO_DIR, 2);
	else if (errno == EROFS)
		ft_putstrs_fd(E_READ_ONLY, file_name, "\n", 2);
	else
		ft_putstrs_fd(E_OPEN_FILE, file_name, "\n", 2);
	free_structs(main);
	exit (EXIT_FAILURE);
}
