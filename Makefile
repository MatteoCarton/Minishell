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
	$(SRC_PATH)/lexer/lexer_token.c \
	$(SRC_PATH)/lexer/lexer_free.c \
	$(SRC_PATH)/expend/expender.c \
	$(SRC_PATH)/expend/expender_env.c \
	$(SRC_PATH)/expend/expender_utils.c \
	$(SRC_PATH)/parser/parser.c \
	$(SRC_PATH)/parser/parser_utils.c \
	$(SRC_PATH)/parser/parser_free.c \
	$(SRC_PATH)/shell/shell_utils.c \
	$(SRC_PATH)/shell/shell_exec.c \
	$(SRC_PATH)/signal/signal.c \
	$(SRC_PATH)/exec/exec_utils.c \
	$(SRC_PATH)/exec/exec_path.c \
	$(SRC_PATH)/exec/exec_builtin.c \
	$(SRC_PATH)/exec/exec_main.c \
	$(SRC_PATH)/exec/exec_external.c \
	$(SRC_PATH)/exec/exec_find_path.c \
	$(SRC_PATH)/exec/pipe_child.c \
	$(SRC_PATH)/exec/pipe_main.c \
	$(SRC_PATH)/exec/pipe_utils.c \
	$(SRC_PATH)/exec/redirections_apply.c \
	$(SRC_PATH)/exec/redirections_out.c \
	$(SRC_PATH)/exec/redirections_in.c \
	$(SRC_PATH)/exec/builtin/ft_pwd.c \
	$(SRC_PATH)/exec/builtin/ft_env.c \
	$(SRC_PATH)/exec/builtin/ft_echo.c \
	$(SRC_PATH)/exec/builtin/ft_exit.c \
	$(SRC_PATH)/exec/builtin/ft_exit2.c \
	$(SRC_PATH)/exec/builtin/ft_cd.c \
	$(SRC_PATH)/exec/builtin/ft_cd_utils.c \
	$(SRC_PATH)/exec/builtin/ft_cd2.c \
	$(SRC_PATH)/exec/builtin/ft_export.c \
	$(SRC_PATH)/exec/builtin/ft_export2.c \
	$(SRC_PATH)/exec/builtin/ft_export3.c \
	$(SRC_PATH)/exec/builtin/ft_unset.c \
	$(SRC_PATH)/exec/builtin/builtin_utils.c

OBJS = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

NAME = minishell
LIBS = -lreadline -Llibft -lft

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)Compiling: libft...$(RESET)"
	@$(MAKE) -C ./libft bonus --silent
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
