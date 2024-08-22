/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:37:43 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:25:24 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	argc_checker(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Error, no arguments needed\n", 2, NULL);
		//exit(EXIT_FAILURE);
	}
}
