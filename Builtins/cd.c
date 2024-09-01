/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/28 18:26:03 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/31 19:00:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_env_path(char **env_array, char *env, t_main *main, int i)
{
	int		len;
	char	*path;
	char	*env_key;
	int		len_env_key;
	char	*equal_pos;

	env_key = get_env_key(main, env);
	len_env_key = ft_strlen(env_key);
	while (env_array[i] && ft_memcmp(env_key, env_array[i], len_env_key))
		i++;
	equal_pos = ft_strchr(env_array[i], '=');
	if (!equal_pos)
		return (free(env_key), NULL);
	len = ft_strlen(equal_pos);
	if (env_array[i])
	{
		path = ft_substr(env_array[i], len_env_key, len);
		if (!path)
			error_function(22, main);
	}
	else
		path = NULL;
	free(env_key);
	return (path);
}

void	set_pwd_export(t_main *main, const char *cwd, t_cd *cd)
{
	cd->argv = malloc(sizeof(char *) * 4);
	if (!cd->argv)
		error_function(27, main);
	cd->argv[0] = ft_strdup("export");
	if (!cd->argv[0])
		error_function(-1, main);
	cd->argv[1] = ft_strdup("PWD=");
	if (!cd->argv[1])
		error_function(-1, main);
	cd->argv[2] = ft_strjoin(cd->argv[1], cwd);
	if (!cd->argv[2])
		error_function(20, main);
	main->env_array = export_cmd(main, cd);
	free(cd->argv[0]);
	free(cd->argv[1]);
	free(cd->argv[2]);
	free(cd->argv);
}

void	set_oldpwd_export(t_main *main, const char *oldpwd, t_cd *cd)
{
	cd->argv = malloc(sizeof(char *) * 4);
	if (!cd->argv)
		error_function(27, main);
	cd->argv[0] = ft_strdup("export");
	if (!cd->argv[0])
		error_function(-1, main);
	cd->argv[1] = ft_strdup("OLDPWD=");
	if (!cd->argv[1])
		error_function(-1, main);
	cd->argv[2] = ft_strjoin(cd->argv[1], oldpwd);
	if (!cd->argv[2])
		error_function(20, main);
	main->env_array = export_cmd(main, cd);
	free(cd->argv[0]);
	free(cd->argv[1]);
	free(cd->argv[2]);
	free(cd->argv);
}

void change_dir(t_main *main, const char *path)
{
    char cwd[BUF_SIZE];
    char oldpwd[BUF_SIZE];
    t_cd *cd;

    cd = malloc(sizeof(t_cd));
    if (!cd)
        error_function(28, main);
    if (!getcwd(oldpwd, BUF_SIZE))
    {
        free(cd);
        return ;
    }
    if (chdir(path) != 0)
    {
        free(cd);
        return ;
    }
    if (!getcwd(cwd, BUF_SIZE))
    {
        free(cd);
        return ;
    }
    set_oldpwd_export(main, oldpwd, cd);
    set_pwd_export(main, cwd, cd);
    free(cd);
}

void	ft_cd(t_main *main, int argc)
{
	char	*path;
	int		i;

	i = 0;
	if (argc < 3)
	{
		if (!main->cmd->args[1] || !ft_strcmp(main->cmd->args[1], "--")
			|| !ft_strcmp(main->cmd->args[1], "~"))
			path = to_home(main, i);
		else if (!ft_strcmp(main->cmd->args[1], "-"))
			path = to_print_pwd(main, i);
		else
		{
			path = ft_strdup(main->cmd->args[1]);
			if (!path)
				error_function(-1, main);
		}
		if (path)
		{
			change_dir(main, path);
			free(path);
		}
	}
	else
		too_many_args(main);
}
