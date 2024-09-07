/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/07 12:43:24 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	is_numeric_overflow(char *str)
{
	char	*max_ll;
	int		len;
	int		i;

	i = 0;
	max_ll = "9223372036854775807";
	len = ft_strlen(str);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		while (i < 19)
		{
			if (str[i] > max_ll[i])
				return (1);
			else if (str[i] < max_ll[i])
				return (0);
			i++;
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
			is_numeric_error_message(main, own_cmd);
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
		parent_error_message(main);
	exit(main->exit_code);
}
