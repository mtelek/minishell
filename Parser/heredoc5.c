/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:40:08 by mtelek            #+#    #+#             */
/*   Updated: 2024/09/01 22:42:36 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	helper_one(t_cmd *own_cmd, int i)
{
	int	len;
	int	j;

	j = 2;
	len = ft_strlen(own_cmd->delimiter[i]);
	if (len > 1 && ((own_cmd->delimiter[i][0] == '"'
			&& own_cmd->delimiter[i][1] == '"')
			|| (own_cmd->delimiter[i][0] == '\''
				&& own_cmd->delimiter[i][1] == '\'')))
	{
		while (j < len)
		{
			own_cmd->delimiter[i][j - 2] = own_cmd->delimiter[i][j];
			j++;
		}
		len -= 2;
		own_cmd->delimiter[i][len] = '\0';
	}
}

void	helper_two(t_cmd *own_cmd, int i)
{
	int	len;

	len = ft_strlen(own_cmd->delimiter[i]);
	if (len > 1 && ((own_cmd->delimiter[i][len - 2] == '"'
			&& own_cmd->delimiter[i][len - 1] == '"')
			|| (own_cmd->delimiter[i][len - 2] == '\''
				&& own_cmd->delimiter[i][len - 1] == '\'')))
	{
		own_cmd->delimiter[i][len - 2] = '\0';
		len -= 2;
	}
}

void	helper_three(t_cmd *own_cmd, int i)
{
	int	len;
	int	j;

	j = 1;
	len = ft_strlen(own_cmd->delimiter[i]);
	if (len > 1 && ((own_cmd->delimiter[i][0] == '"'
			&& own_cmd->delimiter[i][len - 1] == '"')
			|| (own_cmd->delimiter[i][0] == '\'' && own_cmd->delimiter[i][len
				- 1] == '\'')))
	{
		while (j < len - 1)
		{
			own_cmd->delimiter[i][j - 1] = own_cmd->delimiter[i][j];
			j++;
		}
		own_cmd->delimiter[i][len - 2] = '\0';
	}
}

void	remove_surrounding_quotes(t_cmd *own_cmd, int i)
{
	helper_one(own_cmd, i);
	helper_two(own_cmd, i);
	helper_three(own_cmd, i);
}
