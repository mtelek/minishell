/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:20:29 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/04 16:15:15 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void heredoc_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
		rl_on_new_line();
        rl_done = 1;
        g_parent_exit = 130;
    }
}

void	setup_heredoc_signal_handlers(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
