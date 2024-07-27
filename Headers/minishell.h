/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtelek <mtelek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:11:46 by mtelek            #+#    #+#             */
/*   Updated: 2024/07/27 23:21:23 by mtelek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include "error_messages.h"

typedef struct s_operator
{
	char				*operator;
	int					type;
	struct s_operator	*next;
	struct s_operator	*prev;
}						t_operator;

typedef struct s_lexer
{
	char				*str;
	int					type;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

// INIT
void					init_operators(t_operator **head);
void					get_tokens(char *input, t_operator *operators,
							t_lexer **lexer);
int						get_type(char *str);

// NUMBER_OF_WORDS
int						number_of_words(char *input, t_operator *operators);
int						checking_for_doubles(char *input, int i);
int						qoutes_handler(char *input, int i);
int						qoutes_checker(char *input, char check, int i);
int						is_operator(char c1, char c2, t_operator *operators);
int						op_check(char *op, t_operator *operators);
char					setting_c2(char c2);

// CREATING_WORDS
char					*getting_word(char *input, t_operator *operators,
							t_lexer *lexer);
char					*creating_word_wout_o(char *input, int i,
							t_operator *operators, t_lexer *lexer);
int						calculating_end(char *input, int i,
							t_operator *operators);
char					*creating_string(int start, int end, char *input);
int						getting_word_i_start(char *input, int i);
int						null_terminator_check(char *input, int i);

// SYNTAX_CHECK
bool					syntax_check(t_operator *operators, t_lexer *lexer);
bool					syntax_doubles_same(t_operator *temp_op, t_lexer *lexer,
							t_lexer *temp_lex);
bool					syntax_doubles_diff(t_lexer *lexer);
bool					checking_combinaton(t_lexer *lexer);
bool					checking_lex(char *str);

// ERRORS
void					error_function(int error_type, t_operator *operators,
							t_lexer *lexer);
void					ok_free_function(t_operator *operators, t_lexer *lexer);

// CHECKERS
void					argc_checker(int argc, char **argv);

// LIBFT UTILS
void					*ft_memmove(void *dest, const void *src, size_t n);
int						ft_isspace(int c);
char					*ft_strdup(const char *s1);
void					*ft_memcpy(void *dest, const void *src, size_t n);
size_t					ft_strlen(const char *str);
int						ft_strncmp(const char *str1, const char *str2,
							size_t n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);

#endif