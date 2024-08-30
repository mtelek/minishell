/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:50:14 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/30 00:32:50 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	add_node(t_expand_node **head, char *str, t_main *main)
{
	t_expand_node	*new_node;
	t_expand_node	*last;

	new_node = malloc(sizeof(t_expand_node));
	if (!new_node)
		error_function(25, main);
	new_node->str = str;
	new_node->next = NULL;
	new_node->to_expand = false;
	if (*head == NULL)
		*head = new_node;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

char	*join_list(t_expand_node *expand, t_main *main)
{
	size_t			total_len;
	char			*joined_str;
	t_expand_node	*current;
	size_t			offset;

	total_len = 0;
	current = expand;
	while (current)
	{
		total_len += ft_strlen(current->str);
		current = current->next;
	}
	joined_str = malloc(total_len + 1);
	if (!joined_str)
		error_function(-1, main);
	current = expand;
	offset = 0;
	while (current)
	{
		ft_strlcpy(joined_str + offset, current->str, total_len - offset + 1);
		offset += ft_strlen(current->str);
		current = current->next;
	}
	joined_str[offset] = '\0';
	return (joined_str);
}

void	free_list(t_expand_node *expand)
{
	t_expand_node	*temp;

	while (expand)
	{
		temp = expand;
		expand = expand->next;
		free(temp->str);
		free(temp);
	}
}

void	join_expand_node(t_expand_node *expand, t_main *main, t_lexer *lexer)
{
	if (expand == NULL)
	{
		free(lexer->str);
		lexer->str = ft_strdup("");
		if (!lexer->str)
			error_function(-1, main);
		return ;
	}
	free(lexer->str);
	lexer->str = join_list(expand, main);
	free_list(expand);
	if (!lexer->str)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
}

void	split_up_by_dollar(t_expand_node **head, t_lexer *lexer, t_main *main)
{
	int		i;
	int		start;
	char	*substr;

	i = 0;
	start = 0;
	while (lexer->str[i])
	{
		if (lexer->str[i] == '$')
		{
			if (i > start)
			{
				substr = strndup(lexer->str + start, i - start);
				add_node(head, substr, main);
			}
			start = i;
		}
		i++;
	}
	if (i > start)
	{
		substr = strndup(lexer->str + start, i - start);
		add_node(head, substr, main);
	}
}
