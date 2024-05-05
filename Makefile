# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 18:09:00 by momrane           #+#    #+#              #
#    Updated: 2024/05/05 19:33:21 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR		= \033[0;39m
GREEN 			= \033[0;92m
CYAN 			= \033[0;96m

# Name
NAME 			= cube3D

# Directories
SRC_DIR			= ./src
OBJ_DIR 		= ./obj
INC_DIR 		= ./inc
LIB_DIR 		= ./lib
BIN_DIR 		= ./bin
UTILS_DIR		= $(SRC_DIR)/utils
PARSING_DIR		= $(SRC_DIR)/parsing
MINILIBX_DIR	= $(LIB_DIR)/mlx
LIBFT_DIR		= $(LIB_DIR)/libft

# Libs
MINILIBX		= $(MINILIBX_DIR)/libmlx.a
LIBFT			= $(LIBFT_DIR)/libft.a
LIBS 			= $(LIBFT) $(MINILIBX)

# Compilation
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3
MLX_FLAGS		= -Lmlx -L/$(LIB_DIR) -Imlx -lXext -lX11 -lm -lz

# Sources
PARSING		:=	$(PARSING_DIR)/parsing.c
UTILS		:=	$(UTILS_DIR)/utils.c $(UTILS_DIR)/free.c
SRC			:=	$(SRC_DIR)/main.c $(PARSING) $(UTILS)

# Objects
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

val: $(NAME)
	@valgrind ./$(NAME)

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	@$(CC) -I $(INC_DIR) $(OBJ) $(LIBS) $(MLX_FLAGS) -o ./$(NAME)
	@echo "$(GREEN)cub3d compiled !$(DEF_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -Imlx -O3 -c $< -o $@

# libft
$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MINILIBX):
	@make -sC $(MINILIBX_DIR) all

clean:
	@make -sC ./lib/mlx clean
	@make -sC ./lib/libft clean
	@rm -rf $(BIN_DIR)
	@echo "$(CYAN)Binaries files has been cleaned !$(DEF_COLOR)"

fclean: clean
	@make -sC ./lib/mlx clean
	@make -sC ./lib/libft fclean
	@rm -f $(NAME)
	@echo "$(CYAN)The exec files has been cleaned !$(DEF_COLOR)"

re: fclean clean all
	@echo "$(GREEN)Everything cleaned and rebuilt !$(DEF_COLOR)"

.PHONY: all clean fclean re