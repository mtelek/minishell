/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:10:39 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/31 14:22:56 by ibaranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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
	ft_putstrs_fd("bash:  ",
		main->cmd->args[0], ": too many arguments\n", 2);
	main->exit_code = 1;
}
