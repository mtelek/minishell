/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:44:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/15 22:03:13 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_txt_name(t_main *main, int type)
{
	while (main->lexer != NULL)
	{
		if (main->lexer->next && main->lexer->type == type)
			return (main->lexer->next->str);
		main->lexer = main->lexer->next;
	}
	return (NULL);
}

void	set_infile_fd(int *input_fd, t_main *main)
{
	char	*file_name;

	file_name = get_txt_name(main, INPUT_RED);
	*input_fd = open(file_name, O_RDONLY);
	if (*input_fd == -1)
		open_failed(main, file_name);
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
		set_infile_fd(&main->parser->input_fd[i], main);
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
	}
}

void	init_infile(t_main *main, t_cmd *own_cmd)
{
	alloc_input_f(main, own_cmd);
	switch_fd_infile(main, own_cmd);
}
