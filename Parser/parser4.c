/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:18:59 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/07 14:22:58 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	env_helper(t_cmd *own_cmd, t_main *main)
{
	ft_env(own_cmd, main);
	main->exit_code = 0;
}

void	export_helper(t_cmd *own_cmd, t_main *main)
{
	if (own_cmd->pid == 0)
	{
		if (own_cmd->n_append || own_cmd->n_out || main->parser->n_pipes)
		{
			if (!export_error(own_cmd->args, main))
			{
				ft_export(own_cmd, main, own_cmd->args);
				main->exit_code = 0;
			}
		}
	}
	if (own_cmd->pid != 0)
	{
		if (!own_cmd->n_append && !own_cmd->n_out && !main->parser->n_pipes)
		{
			if (!export_error(own_cmd->args, main))
			{
				ft_export(own_cmd, main, own_cmd->args);
				main->exit_code = 0;
			}
		}
	}
}

void	unset_helper(t_cmd *own_cmd, t_main *main)
{
	if (!unset_error(own_cmd->args, main))
	{
		ft_unset(own_cmd, main, own_cmd->args);
		main->exit_code = 0;
	}
}
