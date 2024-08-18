/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:49:08 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/18 22:05:41 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

//can be echo <<haha and echo << haha as well
//check for 'delimeter'

void	set_heredoc_fd(int *heredoc_fd, t_main *main)
{
    char *line;
    char *content;
    char    *temp_line;
    char *delimiter;
    int   pipe_fd[2];

    content = NULL;
    temp_line = NULL;
    delimiter = get_txt_name(main, HEREDOC);
    if (pipe(pipe_fd) == -1)
        pipe_failed(main);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            free(content);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            content = ft_strjoin(content, "\n");
            free(temp_line);
            free(line);
            break;
        }
        if (!content)
        {
            temp_line = ft_strdup(line); //need error message
            content = ft_strjoin(temp_line, "\n");
        }
        else
        {
            temp_line = ft_strjoin(line, "\n");
            content = ft_strjoin(content, temp_line);
        }
    }
    if (content)
    {
        ft_putstr_fd(content, 1);
        free(content);
        main->heredoc_flag = 0;
    }
    close(pipe_fd[1]);
    *heredoc_fd = pipe_fd[0];
}

void	alloc_heredoc_f(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	main->parser->heredoc_fd = malloc(own_cmd->n_heredoc * sizeof(int));
	if (!main->parser->heredoc_fd)
		error_function(15, main);
	while (i < own_cmd->n_heredoc)
	{
		set_heredoc_fd(&main->parser->heredoc_fd[i], main);
		i++;
	}
}

void	switch_fd_heredoc(t_main *main, t_cmd *own_cmd)
{
	int	i;

	i = 0;
	while (i < own_cmd->n_heredoc)
	{
		if (dup2(main->parser->heredoc_fd[i], STDIN_FILENO) < 0)
			dup_failed(main, main->parser->heredoc_fd[i], STDIN_FILENO);
		if (close(main->parser->heredoc_fd[i]) == -1)
			close_failed(main, main->parser->heredoc_fd[i]);
		i++;
	}
}

void	init_heredoc(t_main *main, t_cmd *own_cmd)
{
	alloc_heredoc_f(main, own_cmd);
	switch_fd_heredoc(main, own_cmd);
}
