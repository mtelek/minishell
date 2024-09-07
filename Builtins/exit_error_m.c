/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:39:07 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/07 12:43:49 by mtelek           ###   ########.fr       */
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

void	is_numeric_error_message(t_main *main, t_cmd *own_cmd)
{
	ft_putstrs_fd("bash: exit: ", own_cmd->args[1], NULL,
		STDERR_FILENO);
	ft_putstrs_fd(": ", "numeric argument required\n", NULL,
		STDERR_FILENO);
	main->exit_code = 2;
}

void	parent_error_message(t_main *main)
{
	free_at_exit(main);
	ft_putstr_fd(EXIT, STDERR_FILENO);
}
