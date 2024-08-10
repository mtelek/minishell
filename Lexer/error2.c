/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:03:45 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/10 16:57:38 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	error_type10(int error_type)
{
	if (error_type == 1)
		ft_putstr_fd(MF_OPERATOR, 2);
	else if (error_type == 2)
		ft_putstr_fd(MF_LEXER, 2);
	else if (error_type == 3)
		ft_putstr_fd(MF_WORD, 2);
	else if (error_type == 4)
		ft_putstr_fd(MF_CMD_TABLE, 2);
	else if (error_type == 5)
		ft_putstr_fd(MF_CMD_ARGS, 2);
	else if (error_type == 6)
		ft_putstr_fd(MF_CMD_CMD, 2);
	else if (error_type == 7)
		ft_putstr_fd(MF_PARSER, 2);
	else if (error_type == 8)
		ft_putstr_fd(MF_PIPES, 2);
	else if (error_type == 9)
		ft_putstr_fd(MF_ONE_PIPE, 2);
	else if (error_type == 10)
		ft_putstr_fd(ERROR_PIPE, 2);
}

void	error_type20(int error_type)
{
	if (error_type == 11)
		ft_putstr_fd(ERROR_FORK, 2);
	else if (error_type == 12)
		ft_putstr_fd(ERROR_DUP2, 2);
	else if (error_type == 13)
		ft_putstr_fd(MF_INPUT_FD, 2);
	else if (error_type == 14)
		ft_putstr_fd(ERROR_OPEN, 2);
	else if (error_type == 15)
		ft_putstr_fd(MF_OUPUT_FD, 2);
	else if (error_type == 16)
		ft_putstr_fd(MF_APPEND_OUT, 2);
	else if (error_type == 17)
		ft_putstr_fd(ERROR_CLOSE, 2);
}
