# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 18:09:00 by momrane           #+#    #+#              #
#    Updated: 2024/07/02 11:09:10 by vvaudain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR		:= \033[0;39m
GREEN 			:= \033[0;92m
CYAN 			:= \033[0;96m

# Name
NAME 			:= cub3D

# Directories
SRC_DIR			:= ./src
TOOLS_DIR		:= $(SRC_DIR)/tools
PARSING_DIR		:= $(SRC_DIR)/parsing
MLX_DIR			:= $(SRC_DIR)/mlx
RAYTRACING_DIR	:= $(SRC_DIR)/raytracing
OBJ_DIR 		:= ./obj
INC_DIR 		:= ./inc
LIB_DIR 		:= ./lib
BIN_DIR 		:= ./bin
MINILIBX_DIR	:= $(LIB_DIR)/minilibx-linux
LIBFT_DIR		:= $(LIB_DIR)/libft

# Libs
MINILIBX		:= $(MINILIBX_DIR)/libmlx.a
LIBFT			:= $(LIBFT_DIR)/libft.a
LIBS 			:= $(LIBFT) $(MINILIBX)

# Compilation
CC				:= cc
CFLAGS			:= -g3 -MMD #-Wall -Wextra -Werror
LDLIBS			:= -lft -lmlx -lXext -lX11 -lm
LDFLAGS			:= -L$(LIBFT_DIR) -L$(MINILIBX_DIR)
VAL_FLAGS		:= --leak-check=full --track-origins=yes --track-fds=yes

# Sources

TOOLS		:=	$(TOOLS_DIR)/free.c \
				$(TOOLS_DIR)/ft_splitmore.c \
				$(TOOLS_DIR)/init.c \
				$(TOOLS_DIR)/utils.c \
				$(TOOLS_DIR)/utils2.c \
				$(TOOLS_DIR)/utils3.c
				
RAYTRACING	:=	$(RAYTRACING_DIR)/draw.c \
				$(RAYTRACING_DIR)/img.c \
				$(RAYTRACING_DIR)/move.c \
				$(RAYTRACING_DIR)/wallheight.c
				
PARSING		:=	$(PARSING_DIR)/analyze.c \
				$(PARSING_DIR)/analyze2.c \
				$(PARSING_DIR)/ft_check_file.c \
				$(PARSING_DIR)/ft_find_player.c \
				$(PARSING_DIR)/ft_get_all_lines.c \
				$(PARSING_DIR)/ft_map_is_closed.c \
				$(PARSING_DIR)/parsing.c

MLX			:=	$(MLX_DIR)/event.c \
				$(MLX_DIR)/mlx.c

SRC			:=	$(SRC_DIR)/main.c $(TOOLS) $(RAYTRACING) \
				$(PARSING) $(MLX)

# Objects
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Dependencies
DEP 		:= $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o ./$(NAME)
	@echo "$(GREEN)cub3d compiled !$(DEF_COLOR)"

-include $(DEP)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

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