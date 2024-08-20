/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:40 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/20 21:55:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	handle_unset_error(char **args, t_main *main)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!ft_isalpha(args[i][j]) && args[i][j] != '_')
			return (ft_putstrs_fd("unset: ", args[i],
					": invalid parameter name\n", 2, main), 1);
		while (args[i][j])
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
				return (ft_putstrs_fd("unset: ", args[i],
						": invalid parameter name\n", 2, main), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	remove_env_var_from_array(t_main *main, int i, int k, char **args)
{
	int		j;
	int		var_len;
	char	**new_env_array;

	var_len = ft_strlen(args[k]);
	if (ft_strncmp(main->env_array[i], args[k], var_len) == 0
		&& main->env_array[i][var_len] == '=')
	{
		new_env_array = (char **)malloc(sizeof(char *) * (i + 1));
		if (!new_env_array)
			error_function(10, main);
		j = -1;
		while (++j < i)
			new_env_array[j] = main->env_array[j];
		while (main->env_array[i + 1])
		{
			new_env_array[i] = main->env_array[i + 1];
			i++;
		}
		new_env_array[i] = NULL;
		free(main->env_array[j]);
		free(main->env_array);
		main->env_array = new_env_array;
	}
}

void	ft_unset(t_main *main, char **args)
{
	int	i;
	int	k;

	k = 1;
	while (args[k])
	{
		i = 0;
		while (main->env_array[i])
		{
			remove_env_var_from_array(main, i, k, args);
			i++;
		}
		k++;
	}
}
