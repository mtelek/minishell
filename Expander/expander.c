/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:56:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/26 22:03:09 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

// check with valgrind

// what bout null value attached to variable

// tester> echo haha$VAR1
// Value
// tester>

// tester> echo '''$VAR1"''
// ^C
// ^C
// ^C
// ^C
// ^C

// mtelek@c1r2p5:~/CommonCore/minishell$ echo "'"$VAR1"'"
// 'value'
// mtelek@c1r2p5:~/CommonCore/minishell$

char	*get_value(char *env, char *var_equal, t_main *main)
{
	char	*value;

	value = ft_substr(env, ft_strlen(var_equal), ft_strlen(env));
	if (!value)
		error_function(22, main);
	return (value);
}

char	*find_env_row(char **env_array, char *var, t_main *main)
{
	int		i;
	char	*var_equal;
	char	*value;
	size_t	len;

	i = 0;
	len = ft_strlen(var) + 1;
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		error_function(20, main);
	while (env_array[i] != NULL)
	{
		if (ft_strncmp(var_equal, env_array[i], len) == 0)
		{
			value = get_value(env_array[i], var_equal, main);
			free(var_equal);
			return (value);
		}
		i++;
	}
	free(var_equal);
	return (NULL);
}

char	*find_var_name(char *str, t_main *main)
{
	int		i;
	int		start;
	char	*var_name;

	i = find_character(str, '$');
	start = i + 1;
	if (str[start] == '\'')
		return (ft_substr(str, start + 1, ft_strlen(str) - start - 2));
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '\0' && str[i] != 39 && str[i] != 34)
		i++;
	var_name = ft_substr(str, start, i - start);
	if (!var_name)
		error_function(22, main);
	return (var_name);
}



int expander(t_lexer *lexer, t_main *main)
{
	char	*value;
	char	*var_name;
	int		s_double;
	int		e_double;

	delete_all_doubles(lexer, main);
	s_double = qoutes_checker(lexer->str, 34, -1);
	e_double = qoutes_checker(lexer->str, 34, s_double);
	if (e_double)
	{
		if (!s_double)
			remove_quotes(lexer->str, s_double, e_double);
		else if (lexer->str[0] == 34)
			remove_quotes(lexer->str, 0, e_double);
		main->quotes_removed = true;
	}
	var_name = find_var_name(lexer->str, main);
	value = find_env_row(main->env_array, var_name, main);
	if (!value)
		return (ft_putstr_fd("\n", 1), free(var_name), 1);
	free(lexer->str);
	lexer->str = ft_strdup(value);
	if (!lexer->str)
		error_function(-1, main);
    return (free(value), free(var_name), 0);
}

int	decide_to_expand(t_lexer *lexer, t_main *main)
{
	lexer->to_expand = expander_check(lexer->str);
	if (lexer->to_expand == true)
	{
		if (expander(lexer, main) == 1)
			return (1);
	}
	else if (lexer->to_expand == false)
	{
		unused_quotes_removal(lexer, main);
		pinpoint_dollar_sign(lexer, main);
		if (!check_quote_type(lexer->str, 34, 39))
			remove_all_quotes(lexer, main);
	}
	return (0);
}
