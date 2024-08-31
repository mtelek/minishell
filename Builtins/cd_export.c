/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:38 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 17:20:49 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	**ft_cpy_environ(char **env_array, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	i = -1;
	cpy = NULL;
	if (env_array)
		while (env_array[len])
			len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (NULL);
	while (++i < len)
	{
		cpy[i] = ft_strdup(env_array[i]);
		if (!cpy[i])
		{
			free_array(cpy);
			return (NULL);
		}
	}
	return (cpy);
}

static char	**extend_env(t_main *main, int i, int j)
{
	char	**cpy;

	cpy = ft_cpy_environ(main->env_array, 1);
	if (!cpy)
		return (NULL);
	cpy[i] = ft_strdup(main->cmd->args[j]);
	if (!cpy[i])
	{
		free_array(cpy);
		return (NULL);
	}
	free_array(main->env_array);
	return (cpy);
}

static char	**update_env(t_main *main, int i, int j)
{
	char	*new_entry;

	new_entry = ft_strdup(main->cmd->args[j]);
	if (!new_entry)
	{
		free_array(main->env_array);
		return (NULL);
	}
	free(main->env_array[i]);
	main->env_array[i] = new_entry;
	return (main->env_array);
}

char	**export_cmd(t_main *main, int j)
{
	int	i;

	i = -1;
	if (!main->env_array)
	{
		main->env_array = ft_cpy_environ(NULL, 1);
		if (!main->env_array)
			error_function(-1, main);
	}
	while (main->env_array[++i])
	{
		if (!ft_memcmp(main->env_array[i], main->cmd->args[j],
				ft_strlen(main->cmd->args[j])))
			return (update_env(main, i, j));
	}
	return (extend_env(main, i, j));
}
