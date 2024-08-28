NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
SRCDIR = .
OBJDIR = .objs
SRCS = main.c Utils/checker.c Utils/libft_utils1.c Utils/libft_utils2.c Utils/ft_split.c Utils/libft_utils3.c \
		Utils/libft_utils4.c Utils/libft_utils5.c \
		Lexer/creating_word1.c Lexer/creating_word2.c Lexer/syntax_check.c \
		Lexer/init.c Lexer/number_of_words1.c Lexer/number_of_words2.c Lexer/number_of_words3.c \
		Errors_Frees/error.c Errors_Frees/error2.c Errors_Frees/free.c Errors_Frees/failure1.c \
		Errors_Frees/failure2.c Errors_Frees/free2.c \
		Parser/parser.c Parser/creating_cmd_table1.c Parser/creating_cmd_table2.c Parser/quotes_removal.c \
		Parser/pipes.c Parser/pipes2.c Parser/infile.c Parser/outfile.c Parser/append_out.c Parser/parser2.c \
		Parser/heredoc.c Parser/heredoc2.c\
		Sig/sig.c Sig/sig2.c \
		Env/init_env.c \
		Executor/executor.c  Executor/executor2.c \
		Builtins/cd.c Builtins/echo.c Builtins/exit.c Builtins/export.c Builtins/export2.c Builtins/unset.c \
		Builtins/pwd.c Builtins/env.c \
		Expander/expander.c Expander/expander2.c Expander/expander3.c Expander/init_node.c Expander/init_node2.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \


OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all : $(NAME)

$(NAME): $(OBJS)
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean :
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
