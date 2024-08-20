/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:35 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 21:50:42 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	ft_pwd(t_main *main)
{
	char	cwd[BUF_SIZE];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1, main);
		ft_putstr_fd("\n", 1, main);
	}
	else
	{
		ft_putstr_fd("bash: pwd: ", 2, main);
		ft_putstr_fd(strerror(errno), 2, main);
		ft_putstr_fd("\n", 2, main);
		main->exit_code = 1;
		return ;
	}
	main->exit_code = 0;
}
