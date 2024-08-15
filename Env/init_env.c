/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:15:24 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 22:52:51 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	init_env(t_main *main, char **env)
{
	t_env	*new;
	t_env	*last;
	int		i;

	main->env = NULL;
	last = NULL;
	i = -1;
	while (env && env[0] && env[++i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			error_function(0, main);
		new->env = ft_strdup(env[i]);
		if (!new->env)
			error_function(-1, main);
		new->next = NULL;
		if (main->env == NULL)
			main->env = new;
		else
			last->next = new;
		last = new;
	}
	return (0);
}

char	**linked_to_env_array(t_env *env_list, t_main *main)
{
	t_env	*current;
	int		list_size;
	char	**env_array;
	int		i;

	current = env_list;
	list_size = 0;
	i = -1;
	while (current != NULL)
	{
		list_size++;
		current = current->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!env_array)
		error_function(18, main);
	current = env_list;
	while (++i < list_size)
	{
		env_array[i] = strdup(current->env);
		if (!env_array[i])
			error_function(19, main);
		current = current->next;
	}
	env_array[list_size] = NULL;
	return (env_array);
}
