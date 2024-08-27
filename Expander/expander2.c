/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:46:49 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/27 16:09:41 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

// mtelek@c1r2p5:~/CommonCore/minishell$ echo "'"'"'$VAR1'"'"'"
// '"value"'
// mtelek@c1r2p5:~/CommonCore/minishell$ echo ""'"'"'$VAR1'"'"'""
// "'value'"
// mtelek@c1r2p5:~/CommonCore/minishell$ echo """'"'"'$VAR1'"'"'"""
// '"value"'
// mtelek@c1r2p5:~/CommonCore/minishell$ echo """""'"'"'$VAR1'"'"'"""""
// '"value"'
// mtelek@c1r2p5:~/CommonCore/minishell$ echo '"$VAR1"'
// "$VAR1"
// mtelek@c1r2p5:~/CommonCore/minishell$ echo "'"$VAR1"'"
// 'value'
// mtelek@c1r2p5:~/CommonCore/minishell$ echo "'"$VAR1"'"

void	remove_dollar_sign(int dollar_sign_index, t_expand_node *expand, t_main *main)
{
	char	*new_str;
	int		len;

	len = ft_strlen(expand->str);
	new_str = malloc(len - 1);
	if (!new_str)
		error_function(23, main);
	ft_strlcpy(new_str, expand->str, dollar_sign_index + 1);
	ft_strlcpy(new_str + dollar_sign_index, expand->str + dollar_sign_index + 1,
		len - dollar_sign_index);
	free(expand->str);
	expand->str = new_str;
}

void	pinpoint_dollar_sign(t_expand_node *expand, t_main *main)
{
	int	s_single;
	int	dollar_sign;
	int s_double;
	int s_joint;

	dollar_sign = find_character(expand->str, '$');
	if (dollar_sign == -1)
		return ;
	s_single = qoutes_checker(expand->str, 39, -1);
	s_double = qoutes_checker(expand->str, 34, -1);
	if (!s_single && expand->str[0] != 39)
		s_single = -1;
	if (!s_double && expand->str[0] != 34)
		s_double = -1;
	if (s_single == -1)
        s_joint = s_double;	
    else if (s_double == -1)
		s_joint = s_single;
    else
	{
		s_joint = (s_single < s_double) ? s_single : s_double;
	}
	if (s_joint > dollar_sign)
		remove_dollar_sign(dollar_sign, expand, main);
}

int	find_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		check_quote_type(char *str, char c1, char c2)
{
	int i;
	int c1_count;
	int c2_count;

	i = 0;
	c1_count = 0;
	c2_count = 0;
	while (str[i])
	{
		if (str[i] == c1)
			c1_count = 1;
		if (str[i] == c2)
			c2_count = 1;
		i++;
	}
	if (c1_count && c2_count)
		return (1);
	return (0);
}

bool	expander_check(char *str)
{
	int	s_single;
	int	e_single;
	int	s_double;
	int	e_double;
	int	dollar_sign;
	int count_singles;

	dollar_sign = find_character(str, '$');
	if (dollar_sign == -1)
		return (false);
	count_singles = count_character_till_dollar(str, 39);
	if (count_singles % 2 == 1)
		return (false);
	s_single = qoutes_checker(str, 39, -1);
	e_single = qoutes_checker(str, 39, s_single);
	s_double = qoutes_checker(str, 34, -1);
	e_double = qoutes_checker(str, 34, s_double);
	if (!check_quote_type(str, 34, 39) && s_double <= dollar_sign
		&& s_single <= dollar_sign)
		return (true);
	if ((s_single < s_double && s_single != 0) || str[0] == 39)
		if (dollar_sign < s_single || dollar_sign > e_single)
			return (true);
	if ((s_double < s_single && s_double != 0 && s_single < dollar_sign)
			|| (str[0] == 34 && s_single < dollar_sign))
		if (dollar_sign > s_double && dollar_sign < e_double)
			return (true);
	if (s_single == 0 && s_double == 0 && str[0] != 34 && str[0] != 39)
		return (true);
	return (false);
}
