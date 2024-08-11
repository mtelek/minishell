/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:50 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/11 23:28:08 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	exec(t_main *main, t_cmd *own_cmd, char *path, char **env_array)
{
	int	i;

	i = 0;
	if (main->parser->n_pipes == 0)
	{
		if (main->cmd->cmd)
		{
			execve(path, main->cmd->args, env_array);
			error_function(0, main);
			free_env_array(env_array);
			perror("execve"); // to something else here
			exit(1);
		}
	}
	else if (main->parser->n_pipes != 0)
	{
		if (own_cmd != NULL && own_cmd->pid == 0)
		{
			execve(path, own_cmd->args, env_array);
			error_function(0, main);
			free_env_array(env_array);
			perror("execve"); // do something else here
			exit(1);
		}
	}
	free(path); // could do somewhere else as well
	free_env_array(env_array);
	while (i++ < main->parser->n_pipes)
		wait(0);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;

	path = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)))
		if (ft_strcmp(entry->d_name, command) == 0)
			path = ft_strjoin(ft_strjoin(bin, "/"), entry->d_name);
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
		error_function(0, main); //append error fucntion
	bin = ft_split(main->env->env, ':');
	if (!bin[0] && !own_cmd->cmd)
		error_function(0, main); //append error function
	path = check_dir(bin[0] + 5, own_cmd->cmd);
	while (bin[i] && path == NULL)
		path = check_dir(bin[i++], own_cmd->cmd);
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
