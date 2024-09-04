/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:11:18 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/04 20:35:03 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*expand(char *str, t_main *main)
{
	t_expand_node	*expand;
	t_expand_node	*current;
	t_lexer			lexer;

	expand = NULL;
	lexer.str = str;
	cutting_up_lexer_str(&expand, &lexer, main);
	current = expand;
	while (current != NULL)
	{
		current->to_expand = expander_check(current->str, current);
		if (current->to_expand == true)
			if (expander(current, main) == 1)
				no_var_name_found(current, main);
		current = current->next;
	}
	join_expand_node(expand, main, &lexer);
	return (lexer.str);
}

void	find_hd_indicator(t_main *main, t_cmd *cmd)
{
	t_cmd	*temp_cmd;

	temp_cmd = cmd;
	while (temp_cmd != NULL)
	{
		if (temp_cmd->hd_indicator == 1)
		{
			setup_heredoc_signal_handlers();
			get_hd_content(main, temp_cmd);
		}
		temp_cmd = temp_cmd->next;
	}
}

void	delimiter_check(char *delimiter, t_cmd *own_cmd)
{
	int	len;

	if (delimiter)
	{
		len = ft_strlen(delimiter);
		if (len > 1 && delimiter[0] == 39 && delimiter[len - 1] == 39)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[0] == 34 && delimiter[len - 1] == 34)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[0] == 39 && delimiter[1] == 39)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[0] == 34 && delimiter[1] == 34)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[len - 2] == 39
			&& delimiter[len - 1] == 39)
			own_cmd->expander_decider = false;
		else if (len > 1 && delimiter[len - 2] == 34
			&& delimiter[len - 1] == 34)
			own_cmd->expander_decider = false;
	}
}

void	init_delimiter(t_cmd *own_cmd)
{
	int		i;

	i = -1;
	while (++i < own_cmd->n_heredoc)
	{
		delimiter_check(own_cmd->delimiter[i], own_cmd);
		remove_surrounding_quotes(own_cmd, i);
	}
}

void	get_hd_content(t_main *main, t_cmd *own_cmd)
{
	char	*content;

	content = NULL;
	init_delimiter(own_cmd);
	if (ft_strcmp(own_cmd->cmd, "echo") == 0)
	{
		if (echo_and_heredoc(own_cmd->delimiter, main, own_cmd))
			return ;
	}
	else
	{
		content = no_echo_but_heredoc(own_cmd->delimiter,
				content, main, own_cmd);
		if (content)
		{
			own_cmd->hd_content = content;
			if (!own_cmd->hd_content)
				error_function(-1, main);
		}
	}
}
