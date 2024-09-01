/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:24:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/01 22:12:50 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_env_key(t_main *main, char *env)
{
	char	*env_key;

	env_key = ft_strjoin(env, "=");
	if (!env_key)
		error_function(20, main);
	return (env_key);
}

char	*to_home(t_main *main, int i)
{
	char	*path;

	path = get_env_path(main->env_array, "HOME", main, i);
	if (path_helper(1, path, main) == 1)
		return (NULL);
	return (path);
}

char	*to_print_pwd(t_main *main, int i)
{
	char	*path;

	path = get_env_path(main->env_array, "OLDPWD", main, i);
	if (path_helper(2, path, main) == 1)
		return (NULL);
	ft_pwd(main);
	return (path);
}
