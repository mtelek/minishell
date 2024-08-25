/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:56:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/25 23:05:05 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

// valid expanders:
// "$VAR1"
//"${VAR1}"

// errors:
// check with valgrind
// echo "$'VAR1'" doesnt work
// '$"VAR1"' neither does thiss 

//mtelek@c1r2p5:~/CommonCore/minishell$ export {$VAR1}
//bash: export: `{value}': not a valid identifier
//mtelek@c1r2p5:~/CommonCore/minishell$

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
	while (str[i] && str[i] != '=')
		i++;
	var_name = ft_substr(str, start, i);
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
		return (free(var_name), 1);
	free(lexer->str);
	lexer->str = ft_strdup(value);
	if (!lexer->str)
		error_function(-1, main);
	free(var_name);
	free(value);
    return (0);
}
