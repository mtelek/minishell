/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:03:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 02:03:58 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	calling_redirects(t_main *main, t_cmd *own_cmd)
{
	if (own_cmd->pid == 0)
	{
		find_hd_indicator(main, main->cmd);
		if (own_cmd->n_in)
			init_infile(main, own_cmd);
		if (own_cmd->n_out)
			init_outfile(main, own_cmd);
		if (own_cmd->n_append)
			init_append_out(main, own_cmd);
		if (own_cmd->n_heredoc)
		{
			main->heredoc_flag = 1;
			init_heredoc(main, own_cmd);
		}
	}
}

void	wait_for_children(t_main *main)
{
	int	status;
	int	exit_status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			main->exit_code = exit_status;
		}
		else if (WIFSIGNALED(status))
			main->exit_code = 128 + WTERMSIG(status);
	}
}
