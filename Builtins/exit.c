/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/16 23:52:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	ft_exit(t_main *main)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = main->exit_code;
	if (main->cmd->args[1])
	{
		while (main->cmd->args[1][i] && ft_isdigit(main->cmd->args[1][i]))
			i++;
		if (main->cmd->args[1][i])
		{
			ft_putstr_fd(E_NUM_ARG_P1, 2);
			ft_putstr_fd(main->cmd->args[1], 2);
			ft_putstr_fd(E_NUM_ARG_P2, 2);
			exit_status = 2;
		}
		else if (main->cmd->args[2])
		{
			ft_putstr_fd(TOO_MANY_ARGS, 2);
			main->exit_code = 1;
			return ;
		}
		else
			exit_status = ft_atoi(main->cmd->args[1]);
	}
	else
		ft_putstr_fd(EXIT, 2);
	free_structs(main);
	exit(exit_status % 256);
}
