/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:49:08 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/19 01:22:37 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

//can be echo <<haha and echo << haha as well
//check for 'delimeter'
void	set_heredoc_fd(int *heredoc_fd, t_main *main, t_cmd *own_cmd)
{
    char *line;
    char *content = NULL;
    char *delimiter;
    int   pipe_fd[2];

    delimiter = get_txt_name(main, HEREDOC);
    if (pipe(pipe_fd) == -1)
        pipe_failed(main);
    if (ft_strcmp(own_cmd->cmd, "echo") == 0)
    {
        while (1)
        {
            line = readline("> ");
            if (!line || ft_strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
            free(line);
        }
    }
    else
    {
        while (1)
        {
            line = readline("> ");
            if (!line || ft_strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
            content = content ? ft_strjoin(content, line) : ft_strdup(line);
            content = ft_strjoin(content, "\n");
            free(line);
        }
        if (content)
        {
            write(pipe_fd[1], content, ft_strlen(content));
            free(content);
        }
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
		set_heredoc_fd(&main->parser->heredoc_fd[i], main, own_cmd);
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
