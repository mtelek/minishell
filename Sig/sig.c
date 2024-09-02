/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:45:16 by ibaranov          #+#    #+#             */
/*   Updated: 2024/09/02 15:13:18 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
		exit(130);
	else if (sig == SIGQUIT)
		exit(131);
}

void	setup_child_signal_handlers(void)
{
	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	parent_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_parent_exit = 130;
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
	}
}

void	setup_parent_signal_handlers(void)
{
	signal(SIGINT, parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
