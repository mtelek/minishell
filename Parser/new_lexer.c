/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/02 01:08:26 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/02 01:08:26 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_lexer	*create_lexer_node(char *str, t_lexer *prev, t_lexer *next)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(str);
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = get_type(new_node->str);
	new_node->next = next;
	new_node->prev = prev;
	return (new_node);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

void	split_and_insert_lexer_nodes(t_lexer *lexer, t_main *main)
{
	char	**words;
	t_lexer	*current;
	t_lexer	*next_node;
	int		i;

	i = 0;
	if (!lexer || !lexer->str)
		return ;
	words = ft_split(lexer->str, ' ');
	if (!words)
		return ;
	free(lexer->str);
	lexer->str = ft_strdup(words[0]);
	if (!lexer->str)
		error_function(-1, main);
	current = lexer;
	while (words[++i])
	{
		next_node = create_lexer_node(words[i], current, current->next);
		if (current->next)
			current->next->prev = next_node;
		current->next = next_node;
		current = next_node;
	}
	free_words(words);
}
