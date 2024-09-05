/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:26:21 by ibaranov          #+#    #+#             */
/*   Updated: 2024/09/05 18:48:37 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_n_flag(const char *arg)
{
	int	j;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	ft_echo(t_cmd *own_cmd)
{
	int	i;
	int	argc;
	int	no_newline;

	i = 1;
	no_newline = 0;
	argc = count_arg(own_cmd->args);
	while (i < argc && is_n_flag(own_cmd->args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(own_cmd->args[i], 1);
		if (i < argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (!no_newline)
		write(1, "\n", 1);
}
