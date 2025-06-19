GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m
BLUE = \033[34m
RED = \033[31m

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./inc -I./libft

SRC_PATH = ./srcs
OBJ_PATH = ./tmp

SRCS = \
	$(SRC_PATH)/main.c \
	$(SRC_PATH)/lexer/lexer.c \
	$(SRC_PATH)/lexer/lexer_utils.c \
	$(SRC_PATH)/expend/expander.c \
	$(SRC_PATH)/expend/expander_utils.c \
	$(SRC_PATH)/parser/parser.c \
	$(SRC_PATH)/exec/exec.c \
	$(SRC_PATH)/exec/pipe.c \
	$(SRC_PATH)/exec/find_path.c \
	$(SRC_PATH)/exec/redirections.c \
	$(SRC_PATH)/exec/builtin/ft_pwd.c \
	$(SRC_PATH)/exec/builtin/ft_env.c \
	$(SRC_PATH)/exec/builtin/ft_echo.c \
	$(SRC_PATH)/exec/builtin/ft_exit.c \
	$(SRC_PATH)/exec/builtin/ft_cd.c \
	$(SRC_PATH)/exec/builtin/ft_cd2.c \
	$(SRC_PATH)/exec/builtin/ft_export.c \
	$(SRC_PATH)/exec/builtin/ft_export_utils.c \
	$(SRC_PATH)/exec/builtin/ft_unset.c \
	$(SRC_PATH)/exec/builtin/builtin_utils.c \
	$(SRC_PATH)/signal/signal.c \
	$(SRC_PATH)/shell/shell_utils.c \
	$(SRC_PATH)/shell/shell_exec.c

OBJS = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

NAME = minishell
LIBS = -lreadline -Llibft -lft

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)Compiling: libft...$(RESET)"
	@$(MAKE) -C ./libft --silent
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "\n$(GREEN)READY TO EXECUTE: ./minishell$(RESET)\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -s -C libft clean
	@echo "$(GREEN)Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C libft fclean
	@echo "$(GREEN)Executable removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
