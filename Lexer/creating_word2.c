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

int	null_terminator_check(char *input, int i)
{
	if (input[i] == '\0')
		i = 0;
	return (i);
}

int	getting_word_i_start(char *input, int i)
{
	while (input[i] != '\0' && ft_isspace(input[i]))
		i++;
	return (i);
}
