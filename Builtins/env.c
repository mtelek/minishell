/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:42 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/30 14:55:57 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	ft_env(t_main *main)
{
	int	i;

	i = 0;
	if (main->env_array == NULL)
	{
		ft_putstr_fd(ENV_NO_ACCES, STDERR_FILENO);
		main->exit_code = 1;
		return ;
	}
	while (main->env_array[i])
	{
		if (ft_strlen(main->env_array[i]) == 0)
		{
			ft_putstr_fd(EMPTY_ENV_VAR, STDERR_FILENO);
			main->exit_code = 1;
			return ;
		}
		ft_putstr_fd(main->env_array[i], STDIN_FILENO);
		ft_putstr_fd("\n", STDIN_FILENO);
		i++;
	}
	main->exit_code = 0;
}
