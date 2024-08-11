/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:44:10 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/11 23:28:59 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	set_outfile_fd(int *output_fd, t_main *main)
{
	char	*file_name;

	file_name = get_txt_name(main, OUTPUT_RED);
	*output_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*output_fd == -1)
		error_function(14, main); // should specify here as well
}

void	alloc_output_f(t_main *main)
{
	int	i;

	i = 0;
	main->parser->output_fd = malloc(main->parser->n_output_red * sizeof(int));
	if (!main->parser->output_fd)
		error_function(15, main);
	while (i < main->parser->n_output_red)
	{
		set_outfile_fd(&main->parser->output_fd[i], main);
		i++;
	}
}

void	switch_fd_outfile(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->parser->n_output_red)
	{
		if (dup2(main->parser->output_fd[i], STDOUT_FILENO) < 0)
			error_function(12, main);
		close(main->parser->output_fd[i]);
		i++;
	}
}

void	init_outfile(t_main *main)
{
	alloc_output_f(main);
	switch_fd_outfile(main);
}
