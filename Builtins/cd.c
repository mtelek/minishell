/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:33 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/24 00:48:01 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_env_path(char **env_array, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	env = ft_strjoin(env, "=");
	if (!env)
		return (NULL);
	len = ft_strlen(env);
	while (env_array[i] && env_array[i][0] && ft_memcmp(env, env_array[i], len))
		i++;
	if (env_array[i])
		tmp = env_array[i] + len;
	else
		tmp = NULL;
	free(env);
	return (tmp);
}

void	set_oldpwd_export(t_main *main, char *oldpwd)
{
	free_array(main->cmd->args);
	main->cmd->args = (char **)ft_calloc(sizeof(char *), 4);
	main->cmd->cmd = ft_strdup("export");
	if (!main->cmd->cmd)
		error_function(-1, main);
	main->cmd->args[1] = ft_strdup("OLDPWD=");
	if (!main->cmd->args[1])
		error_function(-1, main);
	main->cmd->args[2] = ft_strdup(oldpwd);
	if (!main->cmd->args[2])
		error_function(-1, main);
	main->env_array = export_cmd(main, 1);
	free_array(main->cmd->args);
}

void	set_pwd_export(t_main *main, char *cwd)
{
	main->cmd->args = (char **)ft_calloc(sizeof(char *), 4);
	main->cmd->cmd = ft_strdup("export");
	if (!main->cmd->cmd)
		error_function(-1, main);
	main->cmd->args[1] = ft_strdup("PWD=");
	if (!main->cmd->args[1])
		error_function(-1, main);
	main->cmd->args[2] = ft_strdup(getcwd(cwd, BUF_SIZE));
	if (!main->cmd->args[2])
		error_function(-1, main);
	main->env_array = export_cmd(main, 1);
}

void	change_dir(t_main *main, char *path)
{
	char	cwd[BUF_SIZE];
	char	oldpwd[BUF_SIZE];

	getcwd(oldpwd, BUF_SIZE);
	if (chdir(path) == 0)
	{
		set_oldpwd_export(main, oldpwd);
		set_pwd_export(main, cwd);
	}
	else
	{
		ft_putstrs_fd("bash: cd: ", main->cmd->args[1], ": ", 2);
	}
}

void	ft_cd(t_main *main, int argc)
{
	char	*path;

	errno = 0;
	if (argc < 3)
	{
		if (!main->cmd->args[1] || !ft_memcmp(main->cmd->args[1], "--", 3)
			|| !ft_memcmp(main->cmd->args[1], "~", 2))
			path = get_env_path(main->env_array, "HOME");
		else if (!ft_memcmp(main->cmd->args[1], "-", 2))
			path = get_env_path(main->env_array, "OLDPWD");
		else
			path = main->cmd->args[1];
		change_dir(main, path);
		if (errno > 0)
		{
			ft_putstrs_fd(strerror(errno), "\n", NULL, 2);
			main->exit_code = 1;
		}
	}
	else
	{
		ft_putstrs_fd("bash:  ", main->cmd->args[0],
			": too many arguments\n", 2);
		main->exit_code = 1;
	}
}
