/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:50:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/01 17:59:59 by mtelek           ###   ########.fr       */
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
			return (ft_putstrs_fd(NOT_VAILD_ID_1, args[i], NOT_VALID_ID_2, 2),
				main->exit_code = 1, 1);
		while (args[i][j] && args[i][j] != '=')
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
				return (ft_putstrs_fd(NOT_VAILD_ID_1, args[i], NOT_VALID_ID_2,
						2), main->exit_code = 1, 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	arranging_new_array(t_cmd *own_cmd, int i, int j, char **args)
{
	int		k;
	char	**new_env_array;

	k = 0;
	new_env_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env_array)
		error_function(10, own_cmd->main);
	while (k < i)
	{
		new_env_array[k] = own_cmd->main->env_array[k];
		k++;
	}
	new_env_array[i] = ft_strdup(args[j]);
	if (!new_env_array[i])
		error_function(-1, own_cmd->main);
	new_env_array[i + 1] = NULL;
	free(own_cmd->main->env_array);
	own_cmd->main->env_array = new_env_array;
}

void	declare_x_export(t_cmd *own_cmd)
{
	int	i;

	i = 0;
	bubble_sort_env(own_cmd->main->env_array);
	while (own_cmd->main->env_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(own_cmd->main->env_array[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	update_array(t_cmd *own_cmd, char **args, int i, int j)
{
	if (ft_strncmp(own_cmd->main->env_array[i], args[j], ft_strchr(args[j], '=')
			- args[j]) == 0)
	{
		free(own_cmd->main->env_array[i]);
		own_cmd->main->env_array[i] = ft_strdup(args[j]);
		if (!own_cmd->main->env_array[i])
			error_function(-1, own_cmd->main);
		return (1);
	}
	return (0);
}

void	ft_export(t_cmd *own_cmd, t_main *main, char **args)
{
	int	i;
	int	j;
	int	updated;

	j = 0;
	if (args[j] && !args[j + 1])
	{
		declare_x_export(own_cmd);
		return ;
	}
	while (args[++j])
	{
		i = -1;
		updated = 0;
		while (main->env_array[++i])
		{
			if (update_array(own_cmd, args, i, j) == 1)
			{
				updated = 1;
				break ;
			}
		}
		if (!updated)
			arranging_new_array(own_cmd, i, j, args);
	}
}
