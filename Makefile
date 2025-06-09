NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	srcs/main.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lexer_utils.c \
	srcs/expend/expander.c \
	srcs/expend/expander_utils.c \
	srcs/parser/parser.c \
	srcs/exec/exec.c \
	srcs/exec/builtin/ft_pwd.c \
	srcs/exec/builtin/ft_env.c \
	srcs/signal/signal.c

OBJS = $(SRCS:.c=.o)
INCLUDES = -I./inc -I./libft
LIBS = -lreadline -Llibft -lft

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

libft/libft.a:
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
