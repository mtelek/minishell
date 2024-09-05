/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:02:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 14:37:47 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_file_names(t_cmd *temp_cmd)
{
	if (temp_cmd->append)
	{
		free(temp_cmd->append);
		temp_cmd->append = NULL;
	}
	if (temp_cmd->in)
	{
		free(temp_cmd->in);
		temp_cmd->in = NULL;
	}
	if (temp_cmd->out)
	{
		free(temp_cmd->out);
		temp_cmd->out = NULL;
	}
	if (temp_cmd->delimiter)
	{
		free(temp_cmd->delimiter);
		temp_cmd->delimiter = NULL;
	}
}
