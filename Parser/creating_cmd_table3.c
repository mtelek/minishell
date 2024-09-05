/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_table3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/04 23:29:13 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/04 23:29:13 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_heredoc_redirection(t_lexer **temp_lex, t_cmd **temp_cmd,
		t_main *main)
{
	size_t	old_size;
	size_t	new_size;

	old_size = (*temp_cmd)->n_heredoc * sizeof(char *);
	new_size = ((*temp_cmd)->n_heredoc + 2) * sizeof(char *);
	(*temp_cmd)->delimiter = ft_realloc((*temp_cmd)->delimiter, old_size,
			new_size);
	if (!(*temp_cmd)->delimiter)
		error_function(29, main);
	(*temp_cmd)->delimiter[(*temp_cmd)->n_heredoc++] = (*temp_lex)->next->str;
	(*temp_cmd)->delimiter[(*temp_cmd)->n_heredoc] = NULL;
	(*temp_cmd)->hd_indicator = 1;
}

void	handle_append_redirection(t_lexer **temp_lex, t_cmd **temp_cmd,
		t_main *main)
{
	size_t	old_size;
	size_t	new_size;

	old_size = (*temp_cmd)->n_append * sizeof(char *);
	new_size = ((*temp_cmd)->n_append + 2) * sizeof(char *);
	(*temp_cmd)->append = ft_realloc((*temp_cmd)->append, old_size, new_size);
	if (!(*temp_cmd)->append)
		error_function(29, main);
	(*temp_cmd)->append[(*temp_cmd)->n_append++] = (*temp_lex)->next->str;
	(*temp_cmd)->append[(*temp_cmd)->n_append] = NULL;
}

void	handle_output_redirection(t_lexer **temp_lex, t_cmd **temp_cmd,
		t_main *main)
{
	size_t	old_size;
	size_t	new_size;

	old_size = (*temp_cmd)->n_out * sizeof(char *);
	new_size = ((*temp_cmd)->n_out + 2) * sizeof(char *);
	(*temp_cmd)->out = ft_realloc((*temp_cmd)->out, old_size, new_size);
	if (!(*temp_cmd)->out)
		error_function(29, main);
	(*temp_cmd)->out[(*temp_cmd)->n_out++] = (*temp_lex)->next->str;
	(*temp_cmd)->out[(*temp_cmd)->n_out] = NULL;
}

void	handle_input_redirection(t_lexer **temp_lex, t_cmd **temp_cmd,
		t_main *main)
{
	size_t	old_size;
	size_t	new_size;

	old_size = (*temp_cmd)->n_in * sizeof(char *);
	new_size = ((*temp_cmd)->n_in + 2) * sizeof(char *);
	(*temp_cmd)->in = ft_realloc((*temp_cmd)->in, old_size, new_size);
	if (!(*temp_cmd)->in)
		error_function(29, main);
	(*temp_cmd)->in[(*temp_cmd)->n_in++] = (*temp_lex)->next->str;
	(*temp_cmd)->in[(*temp_cmd)->n_in] = NULL;
}

void	handle_redirections(t_lexer **temp_lex, t_cmd **temp_cmd, int i,
		t_main *main)
{
	if ((i == 0 && (*temp_lex)->type != 6 && (*temp_lex)->next)
		|| ((*temp_lex)->prev && (*temp_lex)->prev->type == 1
			&& (*temp_lex)->type != 6 && (*temp_lex)->next))
	{
		if ((*temp_lex)->type == 6)
		{
			(*temp_cmd)->args[i] = ft_strdup((*temp_lex)->str);
			if (!(*temp_cmd)->args[i])
				error_function(-1, main);
		}
	}
	if ((*temp_lex)->type == INPUT_RED)
		handle_input_redirection(temp_lex, temp_cmd, main);
	else if ((*temp_lex)->type == OUTPUT_RED)
		handle_output_redirection(temp_lex, temp_cmd, main);
	else if ((*temp_lex)->type == APPEND_OUT)
		handle_append_redirection(temp_lex, temp_cmd, main);
	else if ((*temp_lex)->type == HEREDOC)
		handle_heredoc_redirection(temp_lex, temp_cmd, main);
	if (i != 0)
		*temp_lex = (*temp_lex)->next;
}
