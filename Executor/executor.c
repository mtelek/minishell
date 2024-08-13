/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:50 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/13 22:26:34 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	exec(t_main *main, t_cmd *own_cmd, char *path, char **env_array)
{
	int	i;

	i = 0;
	if (own_cmd != NULL && own_cmd->pid == 0)
	{
		if (execve(path, own_cmd->args, env_array) == -1)
			exec_error_function(main, path);
	}
	//if (path)
	//	free(path); // could do somewhere else as well
	free_env_array(env_array);
	while (i++ < main->exec->n_childs)
		wait(0);
}

char	*find_dir(char *bin, char *command)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;
	char			*temp;

	path = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)))
		if (ft_strcmp(entry->d_name, command) == 0)
		{
			temp = ft_strjoin(bin, "/");
			path = ft_strjoin(temp, entry->d_name);
		}
	closedir(dir);
	return (path);
}

char	*find_path(t_main *main, t_cmd *own_cmd)
{
	char	**bin;
	char	*path;
	int		i;

	i = 1;
	while (main->env && main->env->env && ft_strncmp(main->env->env,
			"PATH=", 5) != 0)
		main->env = main->env->next;
	if (main->env == NULL || main->env->next == NULL)
		exec(main, own_cmd, NULL, NULL);//dont know what to do here really
	bin = ft_split(main->env->env, ':');
	if (!bin[0] && !own_cmd->cmd)
		exec(main, own_cmd, NULL, NULL); // dont know what to do here really
	path = find_dir(bin[0] + 5, own_cmd->cmd);
	while (bin[i] && path == NULL)
		path = find_dir(bin[i++], own_cmd->cmd);
	free_bin(bin);
	return (path);
}

void	executor(t_main *main, t_cmd *own_cmd)
{
	char	*path;
	char	**env_array;

	env_array = linked_to_env_array(main->env, main);
	path = find_path(main, own_cmd);
	if (path != NULL)
		exec(main, own_cmd, path, env_array);
	else
		exec(main, own_cmd, own_cmd->cmd, env_array);
}
