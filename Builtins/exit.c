/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/06 17:29:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_at_exit(t_main *main)
{
	free_structs(main);
	free_main(main);
}

void	exit_many_args(t_main *main)
{
	ft_putstr_fd(TOO_MANY_ARGS, STDERR_FILENO);
	if (main->cmd->next == NULL)
		free_at_exit(main);
	exit(1);
}

int	is_numeric_overflow(char *str)
{
	char	*max_ll;
	int		len;

	max_ll = "9223372036854775807";
	len = strlen(str);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		for (int i = 0; i < 19; i++)
		{
			if (str[i] > max_ll[i])
				return (1);
			else if (str[i] < max_ll[i])
				return (0);
		}
	}
	return (0);
}

void	ft_exit(t_cmd *own_cmd, t_main *main)
{
	int	i;

	i = 0;
	if (own_cmd->args[1])
	{
		while (own_cmd->args[1][i] && ft_isdigit(own_cmd->args[1][i]))
			i++;
		if (is_numeric_overflow(own_cmd->args[1]) && main->cmd->next == NULL)
		{
			ft_putstrs_fd("bash: exit: ", own_cmd->args[1], NULL,
				STDERR_FILENO);
			ft_putstrs_fd(": ", "numeric argument required\n", NULL,
				STDERR_FILENO);
			main->exit_code = 2;
		}
		else if (own_cmd->args[1][i])
		{
			ft_putstrs_fd(E_NUM_ARG_P1, own_cmd->args[1], E_NUM_ARG_P2, 2);
			if (main->cmd->next == NULL)
				free_at_exit(main);
			exit(2);
		}
		else if (own_cmd->args[2])
			exit_many_args(main);
		else
			main->exit_code = ft_atoi(own_cmd->args[1]);
	}
	if (main->cmd->next == NULL)
	{
		free_at_exit(main);
		ft_putstr_fd(EXIT, STDERR_FILENO);
	}
	exit(main->exit_code);
}
