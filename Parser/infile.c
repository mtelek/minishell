/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:44:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/29 14:46:12 by ibaranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*get_txt_name(t_main *main, int type, int limit)
{
	static t_lexer	*stat_lexer;
	static int		k;
	t_lexer			*temp;

	if (stat_lexer == NULL)
		stat_lexer = main->lexer;
	k++;
	while (stat_lexer != NULL)
	{
		if (stat_lexer->next && stat_lexer->type == type)
		{
			stat_lexer = stat_lexer->next;
			break ;
		}
		stat_lexer = stat_lexer->next;
	}
	temp = stat_lexer;
	if (k == limit)
	{
		stat_lexer = NULL;
		k = 0;
	}
	return (temp->str);
}

void	set_infile_fd(int *input_fd, t_main *main, t_cmd *own_cmd)
{
	char	*file_name;

	file_name = get_txt_name(main, INPUT_RED, own_cmd->n_in);
	*input_fd = open(file_name, O_RDONLY);
	if (*input_fd == -1)
	{
		free(input_fd);
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
		set_infile_fd(&main->parser->input_fd[i], main, own_cmd);
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
		free(main->parser->input_fd);
		i++;
	}
}

void	init_infile(t_main *main, t_cmd *own_cmd)
{
	alloc_input_f(main, own_cmd);
	switch_fd_infile(main, own_cmd);
}
