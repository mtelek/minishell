/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:44:10 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 00:11:40 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_outfile_fd(int *output_fd, t_main *main, t_cmd *own_cmd, int i)
{
	char	*file_name;

	file_name = own_cmd->out[i];
	*output_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*output_fd == -1)
	{
		free(main->parser->output_fd);
		open_failed(main, file_name);
	}
}

void	alloc_output_f(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	main->parser->output_fd = malloc(own_cmd->n_out * sizeof(int));
	if (!main->parser->output_fd)
		error_function(15, main);
	while (i < own_cmd->n_out)
	{
		set_outfile_fd(&main->parser->output_fd[i], main, own_cmd, i);
		i++;
	}
}

void	switch_fd_outfile(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	while (i < own_cmd->n_out)
	{
		if (dup2(main->parser->output_fd[i], STDOUT_FILENO) < 0)
			dup_failed(main, main->parser->output_fd[i], STDOUT_FILENO);
		if (close(main->parser->output_fd[i]) == -1)
			close_failed(main, main->parser->output_fd[i]);
		i++;
		if (own_cmd->n_out == i)
			free(main->parser->output_fd);
	}
}

void	init_outfile(t_main *main, t_cmd *own_cmd)
{
	alloc_output_f(main, own_cmd);
	switch_fd_outfile(main, own_cmd);
}
