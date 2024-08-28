/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:44:41 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/28 18:22:16 by ibaranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*cd_home(t_main *main, char *path)
{
	path = get_env_path(main->env_array, "HOME");
	if (!path)
	{
		ft_putstrs_fd("bash: cd: HOME not set\n", NULL, NULL, 2);
		main->exit_code = 1;
		return (NULL);
	}
	return (path);
}

char	*cd_oldpwd(t_main *main, char *path)
{
	path = get_env_path(main->env_array, "OLDPWD");
	if (!path)
	{
		ft_putstrs_fd("bash: cd: OLDPWD not set\n", NULL, NULL, 2);
		main->exit_code = 1;
		return (NULL);
	}
	ft_pwd(main);
	return (path);
}
