/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:05 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/07 12:52:48 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	wrong_folder_name(t_main *main, char *path, t_cd *cd)
{
	ft_putstrs_fd("bash: cd: ", path, ": ", 2);
	ft_putstrs_fd(strerror(errno), "\n", NULL, 2);
	main->exit_code = 1;
	free(cd);
}

int	path_helper(int error_type, char *path, t_main *main)
{
	if (!path && error_type == 1)
	{
		ft_putstrs_fd("bash: cd: HOME not set\n", NULL, NULL, 2);
		main->exit_code = 1;
		return (1);
	}
	else if (!path && error_type == 2)
	{
		ft_putstrs_fd("bash: cd: OLDPWD not set\n", NULL, NULL, 2);
		main->exit_code = 1;
		return (1);
	}
	return (0);
}

void	too_many_args(t_main *main)
{
	ft_putstrs_fd("bash:  ", main->cmd->args[0], ": too many arguments\n", 2);
	main->exit_code = 1;
}
