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
# include <errno.h>
#include <sys/ioctl.h>

# define PIPE 1
# define INPUT_RED 2
# define OUTPUT_RED 3
# define HEREDOC 4
# define APPEND_OUT 5

# define BUF_SIZE 4096

extern int					g_parent_exit;

typedef struct s_main		t_main;

typedef struct s_cd
{
	char					**argv;
}							t_cd;

typedef struct s_init_ex_node
{
	int						i;
	int						start;
	bool					in_quotes;
	char					quote_char;
}							t_init_ex_node;

typedef struct s_expand_node
{
	char					*str;
	bool					to_expand;
	int						single_flag;
	struct s_expand_node	*next;
	struct s_expand_node	*prev;
}							t_expand_node;

typedef struct s_builtin
{
	char					**export;
}							t_builtin;

typedef struct s_exec
{
	int						n_childs;
}							t_exec;

typedef struct s_parser
{
	int						**pipes;
	int						n_pipes;
	int						*input_fd;
	int						*output_fd;
	int						*append_out_fd;
	int						*heredoc_fd;
}							t_parser;

typedef struct s_cmd
{
	char					*cmd;
	char					**args;
	int						out_fd;
	int						in_fd;
	__pid_t					pid;
	struct s_cmd			*next;
	struct s_cmd			*prev;
	int						n_in;
	char					**in;
	int						n_out;
	char					**out;
	int						n_append;
	char					**append;
	int						n_heredoc;
	int						hd_indicator;
	char					**delimiter;
	char					*hd_content;
	bool					expander_decider;
	bool					true_command;
	t_main					*main;
}							t_cmd;

typedef struct s_operator
{
	char					*operator;
	int						type;
	struct s_operator		*next;
	struct s_operator		*prev;
}							t_operator;

typedef struct s_lexer
{
	char					*str;
	int						type;
	bool					to_expand;
	struct s_lexer			*next;
	struct s_lexer			*prev;
}							t_lexer;

typedef struct s_main
{
	char					**env_array;
	int						exit_code;
	int						heredoc_flag;
	int						count_line;
	int						count_hd_line;
	bool					quotes_removed;
	t_lexer					*lexer;
	t_operator				*operators;
	t_cmd					*cmd;
	t_parser				*parser;
	t_exec					*exec;
	t_builtin				*builtin;
}							t_main;

// ENV
int							creating_env_array(t_main *main, char **envp);

// INIT
void						init_operators(t_operator **head, t_main *main);
int							get_tokens(char *input, t_lexer **lexer,
								t_main *main);
int							get_type(char *str);

// NUMBER_OF_WORDS
int							number_of_words(char *input, t_main *main);
int							checking_for_doubles(char *input, int i);
int							qoutes_handler(char *input, int i);
int							qoutes_checker(char *input, char check, int i);
int							is_operator(char c1, char c2, t_operator *operators,
								t_main *main);
int							op_check(char *op, t_operator *operators);
int							last_word_check(char *input, int i, t_main *main);
int							ops_check(char *input, int i);
int							calc_n_words_w_op(int n_words, char *input,
								int i);
int							calc_n_words_for_op(char *input, int n_words,
								int i);
int							checker_for_op_space(t_main *main, char *input,
								int i);

// CREATING_WORDS
char						*getting_word(char *input, t_main *main);
char						*creating_word_wout_o(char *input, int i,
								t_main *main);
int							calculating_end(char *input, int i,
								t_operator *operators, t_main *main);
char						*creating_string(int start, int end, char *input);
int							getting_word_i_start(char *input, int i);
int							null_terminator_check(char *input, int i,
								t_main *main);
int							i_check(char *input, int i);

// SYNTAX_CHECK
bool						syntax_check(t_lexer *lexer, t_main *main);
bool						syntax_doubles_same(t_lexer *temp_lex);
bool						syntax_doubles_diff(t_lexer *lexer);
bool						checking_combinaton(t_lexer *lexer);
bool						dot_check(t_lexer *lexer, t_main *main);
bool						quote_check(t_lexer *lexer);

//PARSER
void						parser(t_main *main);
void						alloc_parser(t_main *main);
void						alloc_exec(t_main *main);
void						alloc_builtin(t_main *main);
void						calling_redirects(t_main *main, t_cmd *own_cmd);
void						wait_for_children(t_main *main);
void						find_hd_indicator(t_main *main, t_cmd *cmd);
void						get_hd_content(t_main *main, t_cmd *own_cmd);
void						parser_helper(t_main *main);
void						env_helper(t_cmd *own_cmd, t_main *main);
void						export_helper(t_cmd *own_cmd, t_main *main);
void						unset_helper(t_cmd *own_cmd, t_main *main);
void						split_and_insert_lexer_nodes(t_lexer *lexer,
								t_main *main);
t_lexer						*create_lexer_node(char *str, t_lexer *prev,
								t_lexer *next);

// PARSER/CMD_TABLE
int							count_cmds(t_lexer *lexer);
int							number_of_args(t_lexer *lexer);
void						args_maker(t_cmd *cmd, int n_cmds,
								int n_args, t_main *main);
void						creating_cmd_table(t_main *main);
int							setting_args(t_lexer **temp_lex, t_cmd **temp_cmd,
								int n_args, t_main *main);
void						init_variables(t_cmd **temp);
void						handle_redirections(t_lexer **temp_lex,
								t_cmd **temp_cmd, int i, t_main *main);

//PARSER/PIPES
t_cmd						*init_pipes(t_main *main);
void						set_pipe_fd(int *pipes, t_main *main);
int							fork1(t_main *main);

//PARSER/REDIR
int							red_count(t_lexer *lexer, int type);
void						init_infile(t_main *main, t_cmd *own_cmd);
void						init_outfile(t_main *main, t_cmd *own_cmd);
void						init_append_out(t_main *main, t_cmd *own_cmd);
void						init_heredoc(t_main *main, t_cmd *own_cmd);

//PARSER/QUOTES
void						delete_qoutes(t_expand_node *current);
void						remove_quotes(char *str, int start, int end);

//Executor
void						executor(t_main *main, t_cmd *own_cmd);
char						*find_path(t_main *main, t_cmd *own_cmd, char *dir);
char						*find_dir(char *bin, char *command, t_main *main);
void						free_env_array(char **env_array);
void						free_bin(char **bin);

//BUILTINS
int							count_arg(char **args);
void						free_array(char **array);
char						**export_cmd(t_main *main, t_cd *cd);
void						ft_echo(t_cmd *own_cmd);
void						ft_cd(t_main *main, int argc);
void						ft_exit(t_cmd *own_cmd, t_main *main);
void						ft_export(t_cmd *own_cmd, t_main *main,
								char **args);
char						**ft_cpy_environ(char **env_array, int add);
int							export_error(char **argv, t_main *main);
void						ft_unset(t_cmd *own_cmd, t_main *main, char **args);
void						ft_pwd(t_main *main);
void						ft_env(t_cmd *own_cmd, t_main *main);
int							unset_error(char **args, t_main *main);
char						*get_env_path(char **env_array, char *env,
								t_main *main, int i);
void						bubble_sort_env(char **env_array);
void						swap(char **a, char **b);
int							path_helper(int error_type, char *path,
								t_main *main);
void						too_many_args(t_main *main);
char						*get_env_key(t_main *main, char *env);
char						*to_home(t_main *main, int i);
char						*to_print_pwd(t_main *main, int i);
int							is_env_var_set(const char *env_var);
int							check_declare_x(t_cmd *own_cmd, char **args);
void						declare_x_export(t_cmd *own_cmd);

//HEREDOC
void						get_hd_content(t_main *main, t_cmd *own_cmd);
char						*no_echo_but_heredoc(char **delimiter,
								char *content, t_main *main, t_cmd *own_cmd);
int							echo_and_heredoc(char **delimiter, t_main *main,
								t_cmd *own_cmd);
void						find_hd_indicator(t_main *main, t_cmd *cmd);
char						*expand(char *str, t_main *main);
void						update_count(t_main *main);
char						*join_empty_and_full(t_main *main, char *content);
char						*full_content_fill(t_main *main, t_cmd *own_cmd,
								char *content, char *line);
char						*empty_content_fill(t_main *main, t_cmd *own_cmd,
								char *content, char *line);
void						remove_surrounding_quotes(t_cmd *own_cmd, int i);
void						helper_three(t_cmd *own_cmd, int i);
void						helper_two(t_cmd *own_cmd, int i);
void						helper_one(t_cmd *own_cmd, int i);
int							set_k(t_cmd *own_cmd);

//EXPANDER/INIT
void						cutting_up_lexer_str(t_expand_node **head,
								t_lexer *lexer, t_main *main);
void						join_expand_node(t_expand_node *expand,
								t_main *main, t_lexer *lexer);
void						free_list(t_expand_node *expand);
char						*join_list(t_expand_node *expand,
								t_main *main);
void						add_node(t_expand_node **head, char *str,
								t_main *main);
void						no_quotes(t_expand_node **head, t_lexer *lexer,
								t_main *main, t_init_ex_node *state);
char						*create_substr(t_lexer *lexer, int i,
								int start, t_main *main);

//EXPANDER
void						quotes_and_expander(t_lexer *lexer, t_main *main);
void						decide_to_expand(t_lexer *lexer, t_main *main);
bool						expander_check(char *str, t_expand_node *current);
int							expander(t_expand_node *expand, t_main *main);
char						*find_var_name(char *str, t_main *main);
char						*find_env_row(char **env_array, char *var,
								t_main *main);
int							find_character(char *str, char c);
void						remove_dollar_sign(t_expand_node *expand,
								t_main *main);
void						remove_all_quotes(t_expand_node *expand,
								t_main *main);
void						cross_out_quotes(t_expand_node *expand,
								t_main *main, char c);
int							count_character(char *str, char c);
void						split_up_by_dollar(t_expand_node **head,
								t_lexer *lexer, t_main *main);
void						split_up_by_quotes(t_expand_node **head,
								t_lexer *lexer, t_main *main);
void						no_var_name_found(t_expand_node *current,
								t_main *main);
int							check_for_another_heredoc(t_lexer *temp_lex);
void						delimiter_check(char *delimiter, t_cmd *own_cmd);
void						expand_exit_code(t_expand_node *current,
								t_main *main);
void						init_current(t_lexer *lexer, t_main *main,
								t_expand_node **expand,
								t_expand_node **current);
void						add_singles(t_expand_node *expand, t_main *main);
void						str_check(t_expand_node *expand, t_main *main);
void						check_for_spaces(t_main *main, t_lexer *lexer);
char						*get_value(char *env, char *var_equal,
								t_main *main);

// ERRORS
void						error_function(int error_type, t_main *main);
void						error_type10(int error_type);
void						error_type20(int error_type);
void						execve_error(t_main *main, char *path);
void						exec_error_function(t_main *main, char *path);
void						error_message(int exit_code, char *message,
								char *path, t_main *main);
void						open_failed(t_main *main, char *file_name);
void						dup_failed(t_main *main, int old_fd, int new_fd);
void						close_failed(t_main *main, int fd);
void						closedir_failed(t_main *main, DIR *dir);
void						readdir_failed(t_main *main, DIR *dir);
void						pipe_failed(t_main *main);
void						fork_failed(t_main *main);
void						error_type30(int error_type);

// FREE
void						ok_free_function(t_main *main);
void						free_operator(t_operator *operators);
void						free_lexer(t_lexer *lexer);
void						free_cmd(t_cmd *cmd);
void						free_parser(t_parser *parser);
void						free_exec(t_exec *exec);
void						free_structs(t_main *main);
void						syntax_free(t_main *main);
void						free_main(t_main *main);
void						free_builtin(t_builtin *builtin);
void						free_file_names(t_cmd *temp_cmd);

// CHECKERS
void						argc_checker(int argc, char **argv);

// LIBFT_UTILS
void						*ft_memmove(void *dest, const void *src, size_t n);
int							ft_isspace(int c);
char						*ft_strdup(const char *s1);
void						*ft_memcpy(void *dest, const void *src, size_t n);
size_t						ft_strlen(const char *str);
int							ft_strncmp(const char *str1, const char *str2,
								size_t n);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char *s, int fd);
int							ft_strcmp(const char *s1, const char *s2);
char						**ft_split(char const *s, char c);
char						*ft_strchr(const char *str, int c);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
char						*ft_strjoin(char const *s1, char const *s2);
int							ft_isdigit(int c);
void						*ft_calloc(size_t num, size_t size);
void						ft_bzero(void *s, size_t n);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
int							ft_atoi(const char *str);
int							ft_isalnum(int c);
int							ft_isalpha(int c);
void						ft_putstrs_fd(char *one, char *two,
								char *three, int fd);
char						*ft_itoa(int n);
void						ft_putnbr_fd(int n, int fd);
size_t						ft_strlcpy(char *dest, const char *src,
								size_t size);
char						*ft_strncpy(char *dest, char *src, unsigned int n);
char						*ft_strldup(char *str, int len);
char						*ft_strtrim(char const *s1, char const *set);
char						*ft_strndup(const char *s, size_t n);
char						*ft_strcpy(char *s1, char *s2);
int							is_only_spaces(const char *str);
void						update_global(t_main *main);
void						*ft_realloc(void *ptr, size_t old_size,
								size_t new_size);
int							ft_isnumeric_str(const char *str);

// SIG
void						child_signal_handler(int sig);
void						setup_child_signal_handlers(void);
void						setup_parent_signal_handlers(void);
void						parent_signal_handler(int sig);
void						setup_heredoc_signal_handlers(void);
void						heredoc_signal_handler(int sig);

#endif