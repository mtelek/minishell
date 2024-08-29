/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:26:03 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/29 16:55:11 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_env_path(char **env_array, char *env)
{
	int		i;
	int		len;
	char	*tmp;
	char	*env_key;

	i = 0;
	if (!env)
		return (NULL);
	env_key = ft_strjoin(env, "=");
	if (!env_key)
		return (NULL);
	len = ft_strlen(env_key);
	while (env_array[i] && ft_memcmp(env_key, env_array[i], len))
		i++;
	if (env_array[i])
		tmp = env_array[i] + len;
	else
		tmp = NULL;
	free(env_key);
	return (tmp);
}

void	set_pwd_export(t_main *main, const char *cwd)
{
	main->cmd->args = (char **)ft_calloc(sizeof(char *), 4);
	if (!main->cmd->args)
		error_function(-1, main);
	main->cmd->cmd = ft_strdup("export");
	if (!main->cmd->cmd)
		error_function(-1, main);
	main->cmd->args[1] = ft_strdup("PWD=");
	if (!main->cmd->args[1])
		error_function(-1, main);
	main->cmd->args[2] = ft_strjoin(main->cmd->args[1], cwd);
	if (!main->cmd->args[2])
		error_function(-1, main);
	main->env_array = export_cmd(main, 1);
}

void	set_oldpwd_export(t_main *main, const char *oldpwd)
{
	main->cmd->args = (char **)ft_calloc(sizeof(char *), 4);
	if (!main->cmd->args)
		error_function(-1, main);
	main->cmd->cmd = ft_strdup("export");
	if (!main->cmd->cmd)
		error_function(-1, main);
	main->cmd->args[1] = ft_strdup("OLDPWD=");
	if (!main->cmd->args[1])
		error_function(-1, main);
	main->cmd->args[2] = ft_strjoin(main->cmd->args[1], oldpwd);
	if (!main->cmd->args[2])
		error_function(-1, main);
	main->env_array = export_cmd(main, 1);
}

void	change_dir(t_main *main, const char *path)
{
	char	cwd[BUF_SIZE];
	char	oldpwd[BUF_SIZE];

	if (!getcwd(oldpwd, BUF_SIZE))
		return ;
	if (chdir(path) == 0)
	{
		set_oldpwd_export(main, oldpwd);
		if (!getcwd(cwd, BUF_SIZE))
			return ;
		set_pwd_export(main, cwd);
	}
}

void	ft_cd(t_main *main, int argc)
{
	char	*path;

	path = NULL;
	if (argc < 3)
	{
		if (!main->cmd->args[1] || !ft_strcmp(main->cmd->args[1], "--")
			|| !ft_strcmp(main->cmd->args[1], "~"))
		{
			path = get_env_path(main->env_array, "HOME");
			if (!path)
			{
				ft_putstrs_fd("bash: cd: HOME not set\n", NULL, NULL, 2);
				main->exit_code = 1;
				return ;
			}
		}
		else if (!ft_strcmp(main->cmd->args[1], "-"))
		{
			path = get_env_path(main->env_array, "OLDPWD");
			if (!path)
			{
				ft_putstrs_fd("bash: cd: OLDPWD not set\n", NULL, NULL, 2);
				main->exit_code = 1;
				return ;
			}
			change_dir(main, path);
			ft_pwd(main);
		}
		else
			path = main->cmd->args[1];
		if (path)
			change_dir(main, path);
	}
	else
	{
		ft_putstrs_fd("bash:  ",
			main->cmd->args[0], ": too many arguments\n", 2);
		main->exit_code = 1; 
	}
}
