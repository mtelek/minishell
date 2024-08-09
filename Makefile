NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
SRCDIR = .
OBJDIR = .objs
SRCS = main.c Utils/checker.c Utils/libft_utils1.c Utils/libft_utils2.c \
		Lexer/creating_word1.c Lexer/creating_word2.c Lexer/error.c  Lexer/error2.c\
		Lexer/free.c Lexer/init.c Lexer/number_of_words1.c Lexer/number_of_words2.c Lexer/number_of_words3.c \
		Lexer/syntax_check.c \
		Parser/parser.c Parser/creating_cmd_table1.c Parser/creating_cmd_table2.c Parser/quotes_removal.c \
		Parser/pipes.c Parser/pipes2.c Parser/infile.c Parser/outfile.c Parser/append_out.c\
		Sig/sig.c \

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
