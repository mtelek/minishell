/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:50:55 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/17 20:43:43 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	handle_export_error(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!ft_isalpha(args[i][j]) && args[i][j] != '_')
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		while (args[i][j] && args[i][j] != '=')
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
			{
				ft_putstr_fd("bash: export: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (1);
			}
			j++;
		}
		if (args[i][j] != '=')
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_main *main, char **args)
{
	int		i;
	int		j;
	char	**new_env_array;

	j = 1;
	while (args[j])
	{
		for (i = 0; main->env_array[i]; i++)
		{
			if (strncmp(main->env_array[i], args[j], strchr(args[j], '=') - args[j]) == 0)
			{
				free(main->env_array[i]);
				main->env_array[i] = strdup(args[j]);
				if (!main->env_array[i])
					error_function(-1, main);
				return ;
			}
		}
		new_env_array = (char **)malloc(sizeof(char *) * (i + 2));
		if (!new_env_array)
			error_function(-1, main); //different erro_type needed here
		for (int j = 0; j < i; j++)
			new_env_array[j] = main->env_array[j];
		new_env_array[i] = strdup(args[j]);
		if (!new_env_array[i])
			error_function(-1, main);  //different erro_type needed here
		new_env_array[i + 1] = NULL;
		free(main->env_array);
		main->env_array = new_env_array;
		j++;
	}
}
