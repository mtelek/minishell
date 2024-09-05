/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:29:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 14:07:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	set_k(t_cmd *own_cmd)
{
	int	k;

	if (own_cmd->n_heredoc == 1)
		k = 1;
	else
		k = 0;
	return (k);
}