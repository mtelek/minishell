/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:42 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/24 00:33:15 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	ft_env(t_main *main)
{
	int	i;

	i = 0;
	if (main->env_array == NULL)
	{
		ft_putstr_fd(ENV_NO_ACCES, 2);
		main->exit_code = 1;
		return ;
	}
	while (main->env_array[i])
	{
		if (ft_strlen(main->env_array[i]) == 0)
		{
			ft_putstr_fd(EMPTY_ENV_VAR, 2);
			main->exit_code = 1;
			return ;
		}
		ft_putstr_fd(main->env_array[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	main->exit_code = 0;
}
