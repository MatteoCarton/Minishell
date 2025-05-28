NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c srcs/signal/signal.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I./inc
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
