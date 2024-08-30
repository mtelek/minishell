/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:26:21 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/30 22:23:58 by mtelek           ###   ########.fr       */
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

void	echo_no_new_line(t_cmd *own_cmd, int argc)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 2;
	flag = 0;
	while ((int)ft_strlen(own_cmd->args[1]) > j)
	{
		if (own_cmd->args[1][j] != 'n')
		{
			flag = 1;
			i = 0;
			break ;
		}
		j++;
	}
	while (++i < argc)
	{
		ft_putstr_fd(own_cmd->args[i], 1);
		if (i < argc - 1 && ft_strlen(own_cmd->args[i + 1]))
			write(1, " ", 1);
	}
	if (argc > 1 && flag)
		write(1, "\n", 1);
}

void	ft_echo(t_cmd *own_cmd)
{
	int	i;
	int	argc;

	i = 0;
	argc = count_arg(own_cmd->args);
	if (argc > 1 && own_cmd->args[1][0] == '-'
		&& own_cmd->args[1][1] == 'n')
	{
		echo_no_new_line(own_cmd, argc);
		return ;
	}
	while (++i < argc)
	{
		ft_putstr_fd(own_cmd->args[i], 1);
		if (i < argc - 1 && ft_strlen(own_cmd->args[i + 1]))
			write(1, " ", 1);
	}
	if (argc > 1)
		write(1, "\n", 1);
}
