/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:04:24 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 13:21:48 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_append_out_fd(int *append_out_fd, t_main *main,
			t_cmd *own_cmd, int i)
{
	char	*file_name;

	file_name = own_cmd->append[i];
	*append_out_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*append_out_fd == -1)
	{
		free(main->parser->append_out_fd);
		open_failed(main, file_name);
	}
}

void	alloc_append_out_f(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	main->parser->append_out_fd = malloc(own_cmd->n_append
			* sizeof(int));
	if (!main->parser->append_out_fd)
		error_function(16, main);
	while (i < own_cmd->n_append)
	{
		set_append_out_fd(&main->parser->append_out_fd[i], main, own_cmd, i);
		i++;
	}
}

void	switch_fd_append_out(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	while (i < own_cmd->n_append)
	{
		if (dup2(main->parser->append_out_fd[i], STDOUT_FILENO) < 0)
			dup_failed(main, main->parser->append_out_fd[i], STDOUT_FILENO);
		if (close(main->parser->append_out_fd[i]) == -1)
			close_failed(main, main->parser->append_out_fd[i]);
		i++;
		if (own_cmd->n_append == i)
			free(main->parser->append_out_fd);
	}
}

void	init_append_out(t_main *main, t_cmd *own_cmd)
{
	alloc_append_out_f(main, own_cmd);
	switch_fd_append_out(main, own_cmd);
}
