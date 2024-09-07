/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:38 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/08 00:33:33 by mtelek           ###   ########.fr       */
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

static char	**extend_env(t_main *main, int i, int j, t_cd *cd)
{
	char	**cpy;

	cpy = ft_cpy_environ(main->env_array, 1);
	if (!cpy)
		return (NULL);
	cpy[i] = ft_strdup(cd->argv[j]);
	if (!cpy[i])
	{
		free_array(cpy);
		return (NULL);
	}
	free_array(main->env_array);
	return (cpy);
}

static char	**update_env(t_main *main, int i, int j, t_cd *cd)
{
	char	*new_entry;

	j = 2;
	new_entry = ft_strdup(cd->argv[j]);
	if (!new_entry)
	{
		free_array(main->env_array);
		return (NULL);
	}
	free(main->env_array[i]);
	main->env_array[i] = new_entry;
	return (main->env_array);
}

char	**export_cmd(t_main *main, t_cd *cd)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	if (!main->env_array)
	{
		main->env_array = ft_cpy_environ(NULL, 1);
		if (!main->env_array)
			error_function(-1, main);
	}
	while (main->env_array[++i])
	{
		if (!ft_strncmp(main->env_array[i], cd->argv[j],
				ft_strlen(cd->argv[j]) - 1))
			return (update_env(main, i, j, cd));
	}
	return (extend_env(main, i, j, cd));
}
