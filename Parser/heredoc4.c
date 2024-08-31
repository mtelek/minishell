/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:23:49 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 22:23:49 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*empty_content_fill(t_main *main, t_cmd *own_cmd, char *content, char *line)
{
	char 	*expanded_str;
	char	*temp;
	
	if (own_cmd->expander_decider == true)
		expanded_str = expand(line, main);
	else
		expanded_str = line;
	temp = ft_strjoin(content, expanded_str);
	if (!temp)
		error_function(20, main);
	free(content);
	free(expanded_str);
	content = temp;
	return (content);
}

char	*full_content_fill(t_main *main, t_cmd *own_cmd, char *content, char *line)
{
	char *expanded_str;

	if (own_cmd->expander_decider == true)
		expanded_str = expand(line, main);
	else
	expanded_str = line;
	content = ft_strdup(expanded_str);
	if (!content)
		error_function(-1, main);
	free(expanded_str);
	return (content);
}

char	*join_empty_and_full(t_main *main, char *content)
{
	char	*temp;

	temp = ft_strjoin(content, "\n");
	if (!temp)
		error_function(20, main);
	free(content);
	content = temp;
	return (content);
}

void	update_count(t_main *main, char *line)
{
	free(line);
	main->count_line += main->count_hd_line;
	main->count_hd_line = 0;
}
