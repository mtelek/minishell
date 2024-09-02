/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_word2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:35:06 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:25:45 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	i_check(char *input, int i)
{
	if (!input[i])
		i = 0;
	return (i);
}

int	checking_last_word(char *input, int i, t_main *main)
{
	(void)main;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

int	null_terminator_check(char *input, int i, t_main *main)
{
	if (input[i] == '\0' || !checking_last_word(input, i, main))
		i = 0;
	return (i);
}

int	getting_word_i_start(char *input, int i)
{
	while (input[i] != '\0' && ft_isspace(input[i]))
		i++;
	return (i);
}
