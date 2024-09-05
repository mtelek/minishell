/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:45:16 by ibaranov          #+#    #+#             */
/*   Updated: 2024/09/05 17:32:49 by mtelek           ###   ########.fr       */
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
		rl_on_new_line();
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
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
