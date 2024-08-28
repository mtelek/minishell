/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:26:21 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/28 18:26:24 by ibaranov         ###   ########.fr       */
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

void	echo_no_new_line(t_cmd *own_cmd, int argc, int out_fd)
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
		ft_putstr_fd(own_cmd->args[i], out_fd);
		if (i < argc - 1 && ft_strlen(own_cmd->args[i + 1]))
			write(1, " ", 1);
	}
	if (argc > 1 && flag)
		write(out_fd, "\n", 1);
}

void	ft_echo(t_cmd *own_cmd) // could change out_fd to one
{
	int	i;
	int	argc;
	int	out_fd;

	i = 0;
	out_fd = own_cmd->out_fd;
	argc = count_arg(own_cmd->args);
	if (argc > 1 && own_cmd->args[1][0] == '-'
		&& own_cmd->args[1][1] == 'n')
	{
		echo_no_new_line(own_cmd, argc, out_fd);
		return ;
	}
	while (++i < argc)
	{
		ft_putstr_fd(own_cmd->args[i], out_fd);
		if (i < argc - 1 && ft_strlen(own_cmd->args[i + 1]))
			write(out_fd, " ", 1);
	}
	if (argc > 1)
		write(out_fd, "\n", 1);
}
