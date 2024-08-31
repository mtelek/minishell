/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:42 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 14:16:51 by ibaranov         ###   ########.fr       */
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
	bubble_sort_env(main->env_array);
	while (main->env_array[i])
	{
		if (ft_strlen(main->env_array[i]) == 0)
		{
			ft_putstr_fd(EMPTY_ENV_VAR, STDOUT_FILENO);
			main->exit_code = 1;
			return ;
		}
		ft_putstr_fd(main->env_array[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	main->exit_code = 0;
}
