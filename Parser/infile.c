/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:44:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/09 23:27:10 by mtelek           ###   ########.fr       */
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
		error_function(14, main); // should specify which file failed to open
}

void	alloc_input_f(t_main *main)
{
	int	i;

	i = 0;
	main->parser->input_fd = malloc(main->parser->n_input_red * sizeof(int));
	if (!main->parser->input_fd)
		error_function(13, main);
	while (i < main->parser->n_input_red)
	{
		set_infile_fd(&main->parser->input_fd[i], main);
		i++;
	}
}

void	switch_fd_infile(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->parser->n_input_red)
	{
		if (dup2(main->parser->input_fd[i], STDIN_FILENO) < 0)
			error_function(12, main);
		close(main->parser->input_fd[i]);
		i++;
	}
	// Execute the command directly in the current process
	execvp(main->cmd->cmd, main->cmd->args);
	perror("execvp");
	exit(1);
}

void	init_infile(t_main *main)
{
	alloc_input_f(main);
	switch_fd_infile(main);
}
