/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:37:43 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/22 19:25:14 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argc_checker(int argc, char **argv)
{
	if (argc != 1 || argv[1])
	{
		printf("Error, no arguments needed\n");
		exit(EXIT_FAILURE);
	}
}
