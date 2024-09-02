/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:48:58 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 20:48:58 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	bash_warning(t_main *main, char **delimiter, int i)
{
	char	*count_line;

	main->count_hd_line -= 1;
	count_line = ft_itoa(main->count_line);
	ft_putstrs_fd("bash: warning: here-document at line ",
		count_line, " delimited by end-of-file (wanted `", 2);
	ft_putstrs_fd(delimiter[i], "')\n", NULL, 2);
	free(count_line);
	main->heredoc_flag = 0;
}

int	echo_and_heredoc(char **delimiter, t_main *main, t_cmd *own_cmd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter[i]) == 0)
		{
			if (!line)
				bash_warning(main, delimiter, i);
			i++;
		}
		free(line);
		line = NULL;
		if (i == own_cmd->n_heredoc)
			return (1);
	}
	return (0);
}

int	check_line(t_main *main, char *line, char **delimiter, int *i)
{
	int	flag;

	flag = 0;
	if (!line)
	{
		bash_warning(main, delimiter, (*i));
		free(line);
		flag = 1;
	}
	(*i)++;
	return (flag);
}

char	*content_maker(t_main *main, t_cmd *own_cmd, char *content, char *line)
{
	if (content != NULL)
		content = empty_content_fill(main, own_cmd, content, line);
	else
		content = full_content_fill(main, own_cmd, content, line);
	content = join_empty_and_full(main, content);
	return (content);
}

char	*no_echo_but_heredoc(char **delimiter, char *content,
			t_main *main, t_cmd *own_cmd)
{
	char	*line;
	int		i;
	int		flag;
	int		k;

	i = 0;
	flag = 0;
	if (own_cmd->n_heredoc == 1)
		k = 1;
	else
		k = 0;
	while (1)
	{
		line = readline("> ");
		main->count_hd_line += 1;
		if (!line || ft_strcmp(line, delimiter[i]) == 0)
			flag = check_line(main, line, delimiter, &i);
		if (i == own_cmd->n_heredoc - 1 && !flag && k++)
			content = content_maker(main, own_cmd, content, line);
		flag = 0;
		if (i == own_cmd->n_heredoc)
			break ;
	}
	update_count(main, line);
	return (content);
}
