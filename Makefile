NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
SRCS = main.c Utils/checker.c Utils/libft_utils1.c Utils/libft_utils2.c Lexer/creating_word1.c Lexer/creating_word2.c Lexer/error.c Lexer/init.c Lexer/number_of_words1.c Lexer/number_of_words2.c Lexer/syntax_check.c 
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean :
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
