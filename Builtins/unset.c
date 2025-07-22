/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:40 by mtelek            #+#    #+#             */
/*   Updated: 2025/07/17 17:58:16 by mtelek           ###   ########.fr       */
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

void count_env_vars_to_remove(t_cmd *own_cmd, char *arg, int *env_count, int *vars_to_remove)
{
	int var_len;

	var_len = ft_strlen(arg);
	*env_count = 0;
	*vars_to_remove = 0;

	while (own_cmd->main->env_array[*env_count] != NULL)
	{
		if (ft_strncmp(own_cmd->main->env_array[*env_count], arg, var_len) == 0 &&
			own_cmd->main->env_array[*env_count][var_len] == '=')
		{
			(*vars_to_remove)++;
		}
		(*env_count)++;
	}
}
char **create_new_env_array(t_cmd *own_cmd, t_main *main, char *arg, int new_size)
{
	int i;
	int j;
	int var_len;
	char **new_env_array;

	i = -1;
	j = 0;
	var_len = ft_strlen(arg);
	new_env_array = (char **)malloc(sizeof(char *) * (new_size));
	if (!new_env_array)
		error_function(10, main);
	while (own_cmd->main->env_array[++i] != NULL)
	{
		if (!(ft_strncmp(own_cmd->main->env_array[i], arg, var_len) == 0 &&
			own_cmd->main->env_array[i][var_len] == '=') &&
			is_env_var_set(own_cmd->main->env_array[i]))
			new_env_array[j++] = own_cmd->main->env_array[i];
		else if (is_env_var_set(own_cmd->main->env_array[i]))
			free(own_cmd->main->env_array[i]);
	}
	new_env_array[j] = NULL;
	return (new_env_array);
}
void remove_env_var_from_array(t_cmd *own_cmd, t_main *main, int k, char **args)
{
	int env_count;
	int vars_to_remove;
	char **new_env_array;

	count_env_vars_to_remove(own_cmd, args[k], &env_count, &vars_to_remove);
	new_env_array = create_new_env_array(own_cmd, main, args[k], env_count - vars_to_remove + 1);

	free(own_cmd->main->env_array);
	own_cmd->main->env_array = new_env_array;
}

int	first_check(t_cmd *own_cmd, char **args)
{
	int	var_len;
	int	i;

	var_len = ft_strlen(args[1]);
	i = 0;
	if (args[1] && !args[2])
	{
		while (own_cmd->main->env_array[i] != NULL)
		{
			if (ft_strncmp(own_cmd->main->env_array[i], args[1], var_len) == 0
				&& own_cmd->main->env_array[i][var_len] == '=')
				return (1);
			i++;
		}
		return (own_cmd->main->exit_code = 1, 0);
	}
	return (1);
}

void	ft_unset(t_cmd *own_cmd, t_main *main, char **args)
{
	int	k;

	k = 1;
	if (!args[1])
		return ;
	if (!first_check(own_cmd, args))
		return ;
	while (args[k] != NULL)
	{
		remove_env_var_from_array(own_cmd, main, k, args);
		k++;
	}
}
