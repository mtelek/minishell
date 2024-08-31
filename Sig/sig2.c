/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:20:29 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 20:05:36 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
	}
}

void	setup_heredoc_signal_handlers(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
