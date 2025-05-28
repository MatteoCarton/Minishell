# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:52:47 by hbutt             #+#    #+#              #
#    Updated: 2025/01/20 16:22:47 by hbutt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCDIR = src
OBJDIR = .build

SRC_MAIN = $(SRCDIR)/main.c

SRC_PARSING = $(SRCDIR)/parsing/parser.c \
              $(SRCDIR)/parsing/tokenize.c \
              $(SRCDIR)/parsing/inside_tokenize.c \
              $(SRCDIR)/parsing/check_args.c \
              $(SRCDIR)/parsing/verrif_token.c \
              $(SRCDIR)/parsing/dir_parser.c \
              $(SRCDIR)/parsing/heredoc.c \
              $(SRCDIR)/parsing/not_close_token.c \
              $(SRCDIR)/parsing/dollar.c \
              $(SRCDIR)/parsing/dollar_2.c \
              $(SRCDIR)/parsing/dollar_3.c \
              $(SRCDIR)/parsing/weird_dir.c \
              $(SRCDIR)/parsing/which_token.c \
              $(SRCDIR)/parsing/clean_str.c

SRC_UTILS = $(SRCDIR)/utils/utils_str.c \
            $(SRCDIR)/utils/utils_token.c \
            $(SRCDIR)/utils/utils_print_tokens.c \
            $(SRCDIR)/utils/utils_env.c \
            $(SRCDIR)/utils/pipe_utils.c \
            $(SRCDIR)/utils/signals.c \
            $(SRCDIR)/utils/utils_node.c \
            $(SRCDIR)/utils/split_quote.c \
            $(SRCDIR)/utils/split_quote_2.c \
             $(SRCDIR)/utils/ctrl_c_child.c \
            $(SRCDIR)/utils/utils.c


SRC_BUILTINS = $(SRCDIR)/builtins/ft_cd.c \
	       $(SRCDIR)/builtins/ft_env.c \
               $(SRCDIR)/builtins/ft_exit.c \
	       $(SRCDIR)/builtins/ft_pwd.c \
	       $(SRCDIR)/builtins/ft_unset.c \
	       $(SRCDIR)/builtins/ft_export.c \
               $(SRCDIR)/builtins/ft_export_2.c \
               $(SRCDIR)/builtins/ft_echo.c \
               $(SRCDIR)/builtins/ft_echo_2.c

SRC_EXE = $(SRCDIR)/exe/exe.c \
          $(SRCDIR)/exe/dir_choice.c \
          $(SRCDIR)/exe/path.c \
          $(SRCDIR)/exe/split_for_exe.c \
          $(SRCDIR)/exe/child_dir.c \
          $(SRCDIR)/exe/exe_err.c \
          $(SRCDIR)/exe/utils_exe.c \
          $(SRCDIR)/exe/dir_exe.c

SRC = $(SRC_MAIN) $(SRC_PARSING) $(SRC_UTILS) $(SRC_BUILTINS) $(SRC_EXE)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

#READLINE_PATH = $(HOME)/.brew/Cellar/readline/8.2.13
#READLINE_PATH = $(HOME)/usr/local/opt/readline
READLINE_PATH = $(shell brew --prefix readline)

LFLAGS = -L$(READLINE_PATH)/lib -lreadline -lhistory
INCLUDES = -I$(READLINE_PATH)/include

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) | $(OBJDIR)
	@echo "$(YELLOW)Building libft...$(DEF_COLOR)"
	@make -C ./libft --silent
	@echo "$(YELLOW)Linking $(NAME)...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBFT) -o $(NAME) -I./includes -I./libft $(LFLAGS)
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEF_COLOR)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)/parsing $(OBJDIR)/env $(OBJDIR)/utils $(OBJDIR)/builtins $(OBJDIR)/exe

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./includes -I./libft
	@echo "$(CYAN)Compiled $(notdir $<)$(DEF_COLOR)"

clean:
	@echo "$(RED)Cleaning object files...$(DEF_COLOR)"
	@make clean -C ./libft --silent
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(DEF_COLOR)"
	@make fclean -C ./libft --silent
	@rm -f $(NAME)
	@rm -rf *dSYM*

re: fclean all

.PHONY: all fclean clean re
