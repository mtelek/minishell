/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 13:56:44 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/31 15:00:31 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '\0'
		&& str[i] != 39 && str[i] != 34)
		i++;
	var_name = ft_substr(str, start, i - start);
	if (!var_name)
		error_function(22, main);
	return (var_name);
}

int	expander(t_expand_node *expand, t_main *main)
{
	char	*value;
	char	*var_name;
	int		s_double;
	int		e_double;

	s_double = qoutes_checker(expand->str, 34, -1);
	e_double = qoutes_checker(expand->str, 34, s_double);
	if (e_double)
	{
		if (!s_double)
			remove_quotes(expand->str, s_double, e_double);
		else if (expand->str[0] == 34)
			remove_quotes(expand->str, 0, e_double);
		main->quotes_removed = true;
	}
	var_name = find_var_name(expand->str, main);
	value = find_env_row(main->env_array, var_name, main);
	if (!value)
		return (free(var_name), 1);
	free(expand->str);
	expand->str = ft_strdup(value);
	if (!expand->str)
		error_function(-1, main);
	return (free(value), free(var_name), 0);
}

void	decide_to_expand(t_lexer *lexer, t_main *main)
{
	t_expand_node	*expand;
	t_expand_node	*current;

	expand = NULL;
	cutting_up_lexer_str(&expand, lexer, main);
	current = expand;
	while (current != NULL)
	{
		current->to_expand = expander_check(current->str);
		if (current->to_expand == true)
			if (expander(current, main) == 1)
				no_var_name_found(current, main);
		if (current->to_expand == false)
		{
			if (!ft_strncmp(current->str, "$", 1) && current->str[1] == '\0'
				&& current->next)
				remove_dollar_sign(current, main);
			if ((current->str[0] == 34 && current->str[1] == 34)
				|| (current->str[0] == 39 && current->str[1] == 39))
				remove_all_quotes(current, main);
			delete_qoutes(current);
		}
		current = current->next;
	}
	join_expand_node(expand, main, lexer);
}
