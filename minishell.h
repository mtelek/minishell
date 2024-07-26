/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:46 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/26 12:49:53 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include  <stdlib.h>
# include <stdbool.h>

typedef struct s_operator
{
	char	*operator;
	char 	*name;
	int		type;
	struct s_operator *next;
	struct s_operator *prev;
}				t_operator;

typedef struct s_lexer
{
	char			*str;
    int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

//CHECKERS
void	argc_checker(int argc, char **argv);

//LIBFT UTILS
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_isspace(int c);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *str1, const char *str2, size_t n);

#endif