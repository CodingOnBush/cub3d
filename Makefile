# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 18:09:00 by momrane           #+#    #+#              #
#    Updated: 2024/06/21 11:23:01 by momrane          ###   ########.fr        #
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
MINILIBX_DIR	= $(LIB_DIR)/mlx
LIBFT_DIR		= $(LIB_DIR)/libft

# Libs
MINILIBX		= $(MINILIBX_DIR)/libmlx.a
LIBFT			= $(LIBFT_DIR)/libft.a
LIBS 			= $(LIBFT) $(MINILIBX)

# Compilation
CC				= cc
CFLAGS			= -g3#-Wall -Wextra -Werror
MLX_FLAGS		= -Lmlx -L/$(LIB_DIR) -Imlx -lXext -lX11 -lm -lz

# Sources
SRC			:=	$(wildcard $(SRC_DIR)/*.c)

# Objects
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

all: $(NAME)

e: all
	@./$(NAME) japancoridor.cub

v: $(NAME)
	@valgrind --leak-check=full ./$(NAME) japancoridor.cub

$(NAME): $(LIBS) $(OBJ)
	$(CC) -I $(INC_DIR) $(OBJ) $(LIBS) $(MLX_FLAGS) -o ./$(NAME)
	@echo "$(GREEN)cub3d compiled !$(DEF_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -Imlx -O3 -c $< -o $@

# ---------------------------------- LIBS ---------------------------------- #
$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MINILIBX):
	@make -sC $(MINILIBX_DIR) all

# ---------------------------------- CLEAN ---------------------------------- #
cleanlibs:
	@make -sC $(LIBFT_DIR) fclean
	@make -sC $(MINILIBX_DIR) clean

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(CYAN)Binaries files has been cleaned !$(DEF_COLOR)"

fclean: cleanlibs clean
	@rm -f $(NAME)
	@echo "$(CYAN)The exec files has been cleaned !$(DEF_COLOR)"

re: clean all
	@echo "$(GREEN)bin files cleaned and exec rebuilt !$(DEF_COLOR)"

refull: cleanlibs re
	@echo "$(GREEN)Everything cleaned and rebuilt !$(DEF_COLOR)"

# ---------------------------------- PHONY ---------------------------------- #
.PHONY: all clean fclean re refull v cleanlibs e