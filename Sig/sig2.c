/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:20:29 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/28 16:17:05 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void    heredoc_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        exit(130);
    }
    else if (sig == SIGQUIT)
    {
        (void)sig;
    }
}

void    setup_heredoc_signal_handlers(void)
{
    signal(SIGINT, heredoc_signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
