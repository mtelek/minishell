/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:42:07 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/28 16:16:21 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void    child_signal_handler(int sig)
{
    if (sig == SIGINT)
        exit(130);
    else if (sig == SIGQUIT)
    {
        printf("Quit (core dumped)\n");
        exit(131);
    }
}

void    setup_child_signal_handlers(void)
{
    signal(SIGINT, child_signal_handler);
    signal(SIGQUIT, SIG_IGN);
}

void    parent_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
    }
    else if (sig == SIGQUIT)
    {
		(void)sig;
    }
}

void    setup_parent_signal_handlers(void)
{
    signal(SIGINT, parent_signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
