/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:26:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/02 15:02:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	check_declare_x(t_cmd *own_cmd, char **args)
{
	int	j;

	j = 0;
	if (args[j] && !args[j + 1])
	{
		declare_x_export(own_cmd);
		return (1);
	}
	return (0);
}

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort_env(char **env_array)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	while (env_array[n])
		n++;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				swap(&env_array[j], &env_array[j + 1]);
			}
			j++;
		}
		i++;
	}
}
