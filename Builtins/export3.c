/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:19:34 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/31 14:22:04 by ibaranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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
