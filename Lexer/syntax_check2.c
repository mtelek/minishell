/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaranov <ibaranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:16:55 by ibaranov          #+#    #+#             */
/*   Updated: 2024/08/28 19:58:26 by ibaranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

bool	dot_check(t_lexer *lexer, t_main *main)
{
	if (lexer->str[0] == '.' && lexer->str[1] == '\0' && lexer->next == NULL)
	{
		ft_putstr_fd("bash: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (false);
	}
	if (lexer->str[0] == '.' && lexer->str[1] == '.'
		&& lexer->str[2] == '\0' && lexer->next == NULL)
	{
		ft_putstr_fd("..: command not found\n", 2);
		main->exit_code = 127;
		return (false);
	}
	return (true);
}
