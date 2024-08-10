/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:04:24 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/10 22:35:53 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_append_out_fd(int *append_out_fd, t_main *main)
{
	char	*file_name;

	file_name = get_txt_name(main, APPEND_OUT);
	*append_out_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*append_out_fd == -1)
		error_function(14, main); // should specify which one failed to open
}

void	alloc_append_out_f(t_main *main)
{
	int	i;

	i = 0;
	main->parser->append_out_fd = malloc(main->parser->n_append_out
			* sizeof(int));
	if (!main->parser->append_out_fd)
		error_function(16, main);
	while (i < main->parser->n_append_out)
	{
		set_append_out_fd(&main->parser->append_out_fd[i], main);
		i++;
	}
}

void	switch_fd_append_out(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->parser->n_append_out)
	{
		if (dup2(main->parser->append_out_fd[i], STDOUT_FILENO) < 0)
			error_function(12, main);
		close(main->parser->append_out_fd[i]);
		i++;
	}
}

void	init_append_out(t_main *main)
{
	alloc_append_out_f(main);
	switch_fd_append_out(main);
}