/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:20:29 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 20:42:35 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		exit(130);
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
