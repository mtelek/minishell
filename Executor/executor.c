/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:59:50 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/21 14:38:01 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	exec(t_main *main, t_cmd *own_cmd, char *path)
{
	if (own_cmd->pid == 0)
	{
		if (execve(path, own_cmd->args, main->env_array) == -1)
			exec_error_function(main, path);
	}
}

char	*check_and_construct_path(char *bin, char *command,
		struct dirent *entry)
{
	char	*path;
	char	*temp;

	if (ft_strcmp(entry->d_name, command) == 0)
	{
		temp = ft_strjoin(bin, "/");
		path = ft_strjoin(temp, entry->d_name);
		free(temp);
		return (path);
	}
	return (NULL);
}

char	*find_dir(char *bin, char *command, t_main *main)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*path;

	path = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	errno = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		path = check_and_construct_path(bin, command, entry);
		if (path != NULL)
			break ;
		entry = readdir(dir);
	}
	if (entry == NULL && errno != 0)
		readdir_failed(main, dir);
	if (closedir(dir) == -1)
		closedir_failed(main, dir);
	return (path);
}

char	*find_path(t_main *main, t_cmd *own_cmd, char *dir)
{
	char	**bin;
	char	*path;
	int		i;
	int		len_dir;

	i = 0;
	len_dir = ft_strlen(dir);
	while (main->env_array[i] && ft_strncmp(main->env_array[i], dir,
			len_dir) != 0)
		i++;
	if (main->env_array[i] == NULL)
		exec(main, own_cmd, own_cmd->cmd);
	bin = ft_split(main->env_array[i] + len_dir + 1, ':');
	if (!bin[0] && !own_cmd->cmd)
		exec(main, own_cmd, own_cmd->cmd);
	path = find_dir(bin[0], own_cmd->cmd, main);
	i = 1;
	while (bin[i] && path == NULL)
		path = find_dir(bin[i++], own_cmd->cmd, main);
	free_array(bin);
	return (path);
}

void	executor(t_main *main, t_cmd *own_cmd)
{
	char	*path;

	if (own_cmd->pid == 0)
	{
		main->exit_code = 0;
		path = find_path(main, own_cmd, "PATH=");
		if (path != NULL)
			exec(main, own_cmd, path);
		else
			exec(main, own_cmd, own_cmd->cmd);
	}
}
