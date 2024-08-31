/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:50:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 02:27:30 by mtelek           ###   ########.fr       */
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

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort_env(char **env_array)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	while (env_array[n])
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				swap(&env_array[j], &env_array[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	declare_x_export(t_main *main)
{
	int	i;

	i = 0;
	bubble_sort_env(main->env_array);
	while (main->env_array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(main->env_array[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_export(t_main *main, char **args)
{
	int	i;
	int	j;
	int	updated;

	j = 0;
	if (args[j] && !args[j+1])
	{
		declare_x_export(main);
		return ;
	}
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
