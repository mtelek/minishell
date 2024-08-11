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
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>

# define PIPE 1
# define INPUT_RED 2
# define OUTPUT_RED 3
# define HEREDOC 4
# define APPEND_OUT 5

typedef struct s_env
{
	char				*env;
	struct s_env		*next;
}				t_env;

typedef struct s_parser
{
	int			**pipes;
	int			n_pipes;
	int			*input_fd;
	int			n_input_red;
	int			*output_fd;
	int			n_output_red;
	int			n_append_out;
	int			*append_out_fd;
}				t_parser;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				out_fd;
	int				in_fd;
	__pid_t			pid;
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
	char			**envp;
	t_lexer			*lexer;
	t_operator		*operators;
	t_cmd			*cmd;
	t_parser		*parser;
	t_env			*env;
}					t_main;

//HELPER/PRINTING
void					print_cmd_table(t_cmd *cmd);
void					print_lexer(t_lexer *lexer);

// ENV
int						init_env(t_main *main, char **env);
char					**linked_to_env_array(t_env *env_list, t_main *main);

// INIT
void					init_operators(t_operator **head, t_main *main);
int						get_tokens(char *input, t_lexer **lexer, t_main *main);
int						get_type(char *str);

// NUMBER_OF_WORDS
int						number_of_words(char *input, t_main *main);
int						checking_for_doubles(char *input, int i);
int						qoutes_handler(char *input, int i);
int						qoutes_checker(char *input, char check, int i);
int						is_operator(char c1, char c2, t_operator *operators,
							t_main *main);
int						op_check(char *op, t_operator *operators);
int						last_word_check(char *input, int i, t_main *main);
int						ops_check(char *input, int i);
int						calc_n_words_w_op(int n_words, char *input, int i);
int						calc_n_words_for_op(char *input, int n_words, int i);
int						checker_for_op_space(t_main *main, char *input, int i);

// CREATING_WORDS
char					*getting_word(char *input, t_main *main);
char					*creating_word_wout_o(char *input, int i, t_main *main);
int						calculating_end(char *input, int i,
							t_operator *operators, t_main *main);
char					*creating_string(int start, int end, char *input);
int						getting_word_i_start(char *input, int i);
int						null_terminator_check(char *input, int i, t_main *main);

// SYNTAX_CHECK
bool					syntax_check(t_lexer *lexer);
bool					syntax_doubles_same(t_lexer *temp_lex);
bool					syntax_doubles_diff(t_lexer *lexer);
bool					checking_combinaton(t_lexer *lexer);
bool					checking_lex(char *str);

//PARSER
void					parser(t_main *main);
void					alloc_parser(t_main *main);

// PARSER/CMD_TABLE
int						count_cmds(t_lexer *lexer);
int						number_of_args(t_lexer *lexer);
void					args_maker(t_lexer *lexer, t_cmd *cmd,
							int n_cmds, int n_args);
void					creating_cmd_table(t_main *main);

//PARSER/PIPES
t_cmd					*init_pipes(t_main *main);
void					set_pipe_fd(int *pipes, t_main *main);
int						fork1(t_main *main);

//PARSER/REDIR
int						red_count(t_lexer *lexer, int type);
void					init_infile(t_main *main);
void					init_outfile(t_main *main);
char					*get_txt_name(t_main *main, int type);
void					init_append_out(t_main *main);

//PARSER/QUOTES
void					delete_qoutes(t_lexer *lexer);
void					remove_quotes(char *str, int start, int end);

//Executor
void					executor(t_main *main, t_cmd *own_cmd);
void					free_env_array(char **env_array);
void					free_bin(char **bin);

// ERRORS
void					error_function(int error_type, t_main *main);
void					error_operators(t_operator *operators);
void					error_lexer(int error_type, t_lexer *lexer);
void					error_cmd(int error_type, t_cmd *cmd);
void					error_type10(int error_type);
void					error_type20(int error_type);

// FREE

void					ok_free_function(t_main *main);
void					free_lexer(t_lexer *lexer);
void					free_operator(t_operator *operators);
void					free_cmd(t_cmd *cmd);

// CHECKERS
void					argc_checker(int argc, char **argv);

// LIBFT_UTILS
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
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *str, int c);
char					*ft_substr(char const *s, unsigned int start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);

// SIG
void					handle_sigint(int sig);

#endif