/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:44:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/05 14:07:55 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_infile_fd(int *input_fd, t_main *main, t_cmd *own_cmd, int i)
{
	char	*file_name;

	file_name = own_cmd->in[i];
	*input_fd = open(file_name, O_RDONLY);
	if (*input_fd == -1)
	{
		open_failed(main, file_name);
	}
}

void	alloc_input_f(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	main->parser->input_fd = malloc(own_cmd->n_in * sizeof(int));
	if (!main->parser->input_fd)
		error_function(13, main);
	while (i < own_cmd->n_in)
	{
		set_infile_fd(&main->parser->input_fd[i], main, own_cmd, i);
		i++;
	}
}

void	switch_fd_infile(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	while (i < own_cmd->n_in)
	{
		if (dup2(main->parser->input_fd[i], STDIN_FILENO) < 0)
			dup_failed(main, main->parser->input_fd[i], STDIN_FILENO);
		if (close(main->parser->input_fd[i]) == -1)
			close_failed(main, main->parser->input_fd[i]);
		i++;
		if (own_cmd->n_in == i)
			free(main->parser->input_fd);
	}
}

void	init_infile(t_main *main, t_cmd *own_cmd)
{
	alloc_input_f(main, own_cmd);
	switch_fd_infile(main, own_cmd);
}
