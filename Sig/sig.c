/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:42:07 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/10 22:53:36 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
}
