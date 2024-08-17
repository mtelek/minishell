/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:15:24 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/17 19:10:12 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	creating_env_array(t_main *main, char **envp)
{
	int		i;
	int		env_count;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	main->env_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!main->env_array)
		return (-1);
	for (i = 0; i < env_count; i++)
	{
		main->env_array[i] = strdup(envp[i]);
		if (!main->env_array[i])
		{
			while (i > 0)
				free(main->env_array[--i]);
			free(main->env_array);
			return (-1);
		}
	}
	main->env_array[env_count] = NULL;
	return (0);
}
