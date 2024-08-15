/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:50 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 22:34:36 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	exec(t_main *main, t_cmd *own_cmd, char *path, char **env_array)
{
	int	i;

	i = 0;
	if (execve(path, own_cmd->args, env_array) == -1)
		exec_error_function(main, path);
}

char	*find_dir(char *bin, char *command, t_main *main)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;
	char			*temp;

	path = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	errno = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp(entry->d_name, command) == 0)
		{
			temp = ft_strjoin(bin, "/");
			path = ft_strjoin(temp, entry->d_name);
			free(temp);
			break ;
		}
	}
	if (entry == NULL && errno != 0)
		readdir_failed(main, dir);
	if (closedir(dir) == -1)
		closedir_failed(main, dir);
	return (path);
}

char	*find_path(t_main *main, t_cmd *own_cmd, char **env_array)
{
	char	**bin;
	char	*path;
	int		i;

	i = 1;
	while (main->env && main->env->env && ft_strncmp(main->env->env, "PATH=",
			5) != 0)
		main->env = main->env->next;
	if (main->env == NULL || main->env->next == NULL)
		exec(main, own_cmd, own_cmd->cmd, env_array);
	bin = ft_split(main->env->env, ':');
	if (!bin[0] && !own_cmd->cmd)
		exec(main, own_cmd, own_cmd->cmd, env_array);
	path = find_dir(bin[0] + 5, own_cmd->cmd, main);
	while (bin[i] && path == NULL)
		path = find_dir(bin[i++], own_cmd->cmd, main);
	return (path);
}

void	executor(t_main *main, t_cmd *own_cmd)
{
	char	*path;
	char	**env_array;

	if (own_cmd->pid == 0)
	{
		main->exit_code = 0;
		env_array = linked_to_env_array(main->env, main);
		path = find_path(main, own_cmd, env_array);
		if (path != NULL)
			exec(main, own_cmd, path, env_array);
		else
			exec(main, own_cmd, own_cmd->cmd, env_array);
	}
}
