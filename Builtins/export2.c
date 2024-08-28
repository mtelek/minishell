/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:50:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/28 18:29:45 by ibaranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	export_error(char **args, t_main *main)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!ft_isalpha(args[i][j]) && args[i][j] != '_')
			return (ft_putstrs_fd(NOT_VAILD_ID_1, args[i],
					NOT_VALID_ID_2, 2), main->exit_code = 1, 1);
		while (args[i][j] && args[i][j] != '=')
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
				return (ft_putstrs_fd(NOT_VAILD_ID_1, args[i],
						NOT_VALID_ID_2, 2), main->exit_code = 1, 1);
			j++;
		}
		if (args[i][j] != '=')
			return (ft_putstrs_fd(NOT_VAILD_ID_1, args[i],
					NOT_VALID_ID_2, 2), main->exit_code = 1, 1);
		i++;
	}
	return (0);
}

void	arranging_new_array(t_main *main, int i, int j, char **args)
{
	int		k;
	char	**new_env_array;

	k = 0;
	new_env_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env_array)
		error_function(10, main);
	while (k < i)
	{
		new_env_array[k] = main->env_array[k];
		k++;
	}
	new_env_array[i] = ft_strdup(args[j]);
	if (!new_env_array[i])
		error_function(-1, main);
	new_env_array[i + 1] = NULL;
	free(main->env_array);
	main->env_array = new_env_array;
}

void	ft_export(t_main *main, char **args)
{
	int	i;
	int	j;
	int	updated;

	j = 0;
	while (args[++j])
	{
		i = -1;
		updated = 0;
		while (main->env_array[++i])
		{
			if (ft_strncmp(main->env_array[i],
					args[j], ft_strchr(args[j], '=') - args[j]) == 0)
			{
				free(main->env_array[i]);
				main->env_array[i] = ft_strdup(args[j]);
				if (!main->env_array[i])
					error_function(-1, main);
				updated = 1;
				break ;
			}
		}
		if (!updated)
			arranging_new_array(main, i, j, args);
	}
}
