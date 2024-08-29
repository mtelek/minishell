/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:40 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 19:04:15 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	unset_error(char **args, t_main *main)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!ft_isalpha(args[i][j]) && args[i][j] != '_')
			return (ft_putstrs_fd("unset: ", args[i],
					": invalid parameter name\n", 2), main->exit_code = 1, 1);
		while (args[i][j])
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
				return (ft_putstrs_fd("unset: ", args[i],
						": invalid parameter name\n", 2), main->exit_code = 1,
					1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_values(int *i, int *j, int *env_count)
{
	*i = -1;
	*j = 0;
	*env_count = 0;
}

void remove_env_var_from_array(t_main *main, int k, char **args)
{
    int i;;
    int j;
    int var_len;
    int env_count;
    char **new_env_array;

	init_values(&i, &j,  &env_count);
    var_len = ft_strlen(args[k]);
    while (main->env_array[env_count] != NULL)
        env_count++;
    new_env_array = (char **)malloc(sizeof(char *) * env_count);
    if (!new_env_array)
        error_function(10, main);
    while (main->env_array[++i] != NULL)
    {
        if (!(ft_strncmp(main->env_array[i], args[k], var_len) == 0
			&& main->env_array[i][var_len] == '='))
            new_env_array[j++] = main->env_array[i];
        else
            free(main->env_array[i]);
    }
    new_env_array[j] = NULL;
    free(main->env_array);
    main->env_array = new_env_array;
}

void	ft_unset(t_main *main, char **args)
{
	int	k;

	k = 1;
	while (args[k] != NULL)
	{
		remove_env_var_from_array(main, k, args);
		k++;
	}
}
