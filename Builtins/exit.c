/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/24 01:04:29 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_at_exit(t_main *main)
{
	free_structs(main);
	free_main(main);
}

void	ft_exit(t_main *main)
{
	int	i;

	i = 0;
	if (main->cmd->args[1])
	{
		while (main->cmd->args[1][i] && ft_isdigit(main->cmd->args[1][i]))
			i++;
		if (main->cmd->args[1][i])
		{
			ft_putstrs_fd(E_NUM_ARG_P1, main->cmd->args[1], E_NUM_ARG_P2, 2);
			main->exit_code = 2;
		}
		else if (main->cmd->args[2])
		{
			ft_putstr_fd(TOO_MANY_ARGS, 2);
			main->exit_code = 1;
			return ;
		}
		else
			main->exit_code = ft_atoi(main->cmd->args[1]);
	}
	else
		ft_putstr_fd(EXIT, 2);
	free_at_exit(main);
	exit(main->exit_code);
}
