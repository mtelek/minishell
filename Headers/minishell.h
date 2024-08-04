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
# include <signal.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				op_next;
	int				op_bef;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

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

typedef struct s_main
{
	t_lexer			*lexer;
	t_operator		*operators;
	t_cmd			*cmd;
}					t_main;

// INIT
void					init_operators(t_operator **head);
void					get_tokens(char *input, t_operator *operators,
							t_lexer **lexer);
int						get_type(char *str);

// NUMBER_OF_WORDS
int						number_of_words(char *input, t_operator *operators);
int						calculating_n_words(t_operator *operators, char *input,
							int i, int n_words);
int						checking_for_doubles(char *input, int i);
int						qoutes_handler(char *input, int i);
int						qoutes_checker(char *input, char check, int i);
int						is_operator(char c1, char c2, t_operator *operators);
int						op_check(char *op, t_operator *operators);

// CREATING_WORDS
char					*getting_word(char *input, t_operator *operators);
char					*creating_word_wout_o(char *input, int i,
							t_operator *operators);
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

// PARSER/CMD_TABLE
int						count_cmds(t_lexer *lexer);
int						number_of_args(t_lexer *lexer);
void					args_maker(t_lexer *lexer, t_cmd *cmd,
							int n_cmds, int n_args);
void					creating_cmd_table(t_main *main);

//PARSER/QUOTES
void					delete_qoutes(t_lexer *lexer);
void					remove_quotes(char *str, int start, int end);

// ERRORS
void					error_function(int error_type, t_operator *operators,
							t_lexer *lexer, t_cmd *cmd);
void					error_operators(t_operator *operators);
void					error_lexer(int error_type, t_lexer *lexer);
void					error_cmd(int error_type, t_cmd *cmd);

// FREE

void					ok_free_function(t_operator *operators,
							t_lexer *lexer, t_cmd *cmd);
void					free_lexer(t_lexer *lexer);
void					free_operator(t_operator *operators);
void					free_cmd(t_cmd *cmd);

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
int						ft_strcmp(char *s1, char *s2);

// SIG
void					handle_sigint(int sig);

#endif