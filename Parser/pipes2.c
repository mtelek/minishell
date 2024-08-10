/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:06:46 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/10 18:59:43 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	fork1(t_main *main)
{
	__pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (pid == 0)
			exit(1);
		error_function(11, main);
	}
	return (pid);
}
