/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:42 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 21:49:33 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	ft_env(t_main *main)
{
	int	i;

	i = 0;
	while (main->env_array[i])
	{
		ft_putstr_fd(main->env_array[i], 1, main);
		ft_putstr_fd("\n", 1, main);
		i++;
	}
	main->exit_code = 0;
}
