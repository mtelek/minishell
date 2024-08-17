/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:07:40 by mtelek            #+#    #+#             */
/*   Updated: 2024/08/17 21:36:17 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int handle_unset_error(char **args)
{
    int i;
    int j;

    i = 1;
    while (args[i])
    {
        j = 0;
        if (!ft_isalpha(args[i][j]) && args[i][j] != '_')
        {
            ft_putstr_fd("unset: ", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd(": invalid parameter name\n", 2);
            return (1);
        }
        while (args[i][j])
        {
            if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
            {
                ft_putstr_fd("unset: ", 2);
                ft_putstr_fd(args[i], 2);
                ft_putstr_fd(": invalid parameter name\n", 2);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}


void	ft_unset(t_main *main, char **args)
{
	int		i;
	int		j;
    int     k;
	int		var_len;
	char	**new_env_array;

    k = 1;
    while (args[k])
    {
	    var_len = strlen(args[k]);
	    for (i = 0; main->env_array[i]; i++)
	    {
	    	if (strncmp(main->env_array[i], args[k], var_len) == 0 && main->env_array[i][var_len] == '=')
	    	{
		    	new_env_array = (char **)malloc(sizeof(char *) * i + 1);
		    	if (!new_env_array)
		    		error_function(-1, main);
		    	for (j = 0; j < i; j++)
		    		new_env_array[j] = main->env_array[j];
		    	for (j = i; main->env_array[j + 1]; j++)
		    		new_env_array[j] = main->env_array[j + 1];
		    	new_env_array[j] = NULL;
		    	free(main->env_array[i]);
		    	free(main->env_array);
		    	main->env_array = new_env_array;
	    	}
    	}
        k++;
    }
}
