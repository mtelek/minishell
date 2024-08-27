/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:50:14 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/27 20:34:21 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	add_node(t_expand_node **head, char *str, t_main *main)
{
	t_expand_node	*new_node;
	t_expand_node	*last;

	new_node = malloc(sizeof(t_expand_node));
	if (!new_node)
		error_function(-1, main); // proper one needed
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

int	find_var_ending(t_lexer *lexer, int i)
{
	while (lexer->str[i] && lexer->str[i] != '$' && lexer->str[i] != 34
		&& lexer->str[i] != 39)
		i++;
	return (i);
}

int	real_first_word_check(t_lexer *lexer, int start)
{
	while (lexer->str[start] == 34 || lexer->str[start] == 39)
		start++;
    if (lexer->str[start] == '$')
        return (0);
    else
        return (1);
}

int	cutting_up_lexer_str(t_expand_node **head, t_lexer *lexer, t_main *main)
{
	char	*part;
	int		i;
	int		start;
	int		q;
	int		quote_type;
    int     first_word;

	*head = NULL;
	i = 0;
	start = 0;
    first_word = 0;
	while (lexer->str[i])
	{
		if (lexer->str[i] == '$')
		{
			if (i > start)
			{
				if (real_first_word_check(lexer, start) == 1)
                    first_word = 1;
                if (first_word)
                {
                    part = ft_substr(lexer->str, start, i - start);
				    if (!part)
					    error_function(-1, main);
				    add_node(head, part, main);
				    i++;
                }
			}
			if (i - 1 < 0)
				start = i;
			else
				start = i - 1;
			q = find_var_ending(lexer, i);
			quote_type = 0;
			if (lexer->str[start] == 34 && lexer->str[q] == 34)
				quote_type = 34;
			else if (lexer->str[start] == 39 && lexer->str[q] == 39)
				quote_type = 39;
			while (quote_type && start > 0 && q < (int)ft_strlen(lexer->str))
			{
				if (lexer->str[start - 1] == quote_type && lexer->str[q
					+ 1] == quote_type)
				{
					start--;
					q++;
				}
				else
					break ;
			}
			i = q + 1;
            first_word = 1;
		}
		else
			i++;
	}
	if (i > start)
	{
		part = ft_substr(lexer->str, start, i - start);
		if (!part)
			error_function(-1, main);
		add_node(head, part, main);
	}
	print_expand(*head);
	return (0);
}
