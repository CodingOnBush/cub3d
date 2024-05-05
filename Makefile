# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 18:09:00 by momrane           #+#    #+#              #
#    Updated: 2024/05/05 19:11:07 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR		= \033[0;39m
GREEN 			= \033[0;92m
CYAN 			= \033[0;96m

# Name
NAME 			= cub3D

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
# HEADER			= -I$(INC_DIR) -I$(LIBFT_DIR)/inc -I$(MINILIBX_DIR)

# Sources
PARSING		:=	$(PARSING_DIR)/parsing.c
UTILS		:=	$(UTILS_DIR)/utils.c
SRC			:=	$(SRC_DIR)/main.c $(PARSING) $(UTILS)

# Objects
OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# #Sources
# SRC_FILES 		=	dda draw environment errors ft_gnl_utils ft_gnl hook_utils \
# 					hook image main matrix parsing point utils
# SRC 			= 	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
# OBJ				= 	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

#Rules

# Libs
all: $(NAME)

print:
	@echo $(SRC)
	@echo $(OBJ)

$(NAME): $(LIBS) $(OBJ)
	@$(CC) -I $(INC_DIR) $(OBJ) $(LIBS) $(MLX_FLAGS) -o $(NAME)
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

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(HEADER) -Imlx -O3 -c $< -o $@

# 	@make -sC $(LIBFT_DIR)


# $(NAME): $(LIBS) $(OBJ)
# 	@$(CC) $(HEADER) $(OBJ) $(LIBS) $(MLX_FLAGS) -o $(NAME)
# $(LIBFT):
# 	@echo "$(GREEN)Fdf compiled!$(DEF_COLOR)"
			
# 	@echo "$(GREEN)libft compiled!$(DEF_COLOR)"

# $(FT_PRINTF):
# 	@make -sC $(FT_PRINTF_DIR)
# 	@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

# $(MINILIBX):
# 	@make -sC $(MINILIBX_DIR)
# 	@echo "$(GREEN)Minilibx compiled!$(DEF_COLOR)"

# clean:
# 	@rm -rf $(OBJ_DIR)
# 	@make -sC $(FT_PRINTF_DIR) clean
# 	@make -sC $(LIBFT_DIR) clean
# 	@make -sC $(MINILIBX_DIR) clean
# 	@echo "$(CYAN)Fdf, Minilibx, Libft and ft_printf object files cleaned!$(DEF_COLOR)"

# fclean: clean
# 	@rm -f $(NAME)
# 	@make -sC $(FT_PRINTF_DIR) fclean
# 	@make -sC $(LIBFT_DIR) fclean
# 	@echo "$(CYAN)libftprintf.a, libft.a and fdf cleaned!$(DEF_COLOR)"

# re: fclean $(NAME)
# 	@echo "$(GREEN)Cleaned and rebuilt everything for Fdf!$(DEF_COLOR)"

# norm:
# 	@norminette $(SRC) $(INC_DIR)/*.h

.PHONY:	all clean fclean re


########################################### Makefile from minishell ###########################################
# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2024/03/08 14:34:28 by momrane           #+#    #+#              #
# #    Updated: 2024/05/03 19:04:39 by momrane          ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# # Setup
# NAME 		:=	minishell
# CC			:=	cc
# CFLAGS		:=	-Wall -Wextra -Werror -g3

# # Valgrind
# VAL_FLAGS	:=	--leak-check=full --show-leak-kinds=all --track-origins=yes \
# 				--suppressions=readline.supp

# # Directories
# BIN_DIR 	:=	./bin
# INC_DIR 	:=	./inc
# LIBFT_DIR	:=	./libft

# SRC_DIR		:=	./src
# INIT_DIR	:=	$(SRC_DIR)/init
# LEXER_DIR	:=	$(SRC_DIR)/lexer
# PARSER_DIR	:=	$(SRC_DIR)/parser
# EXEC_DIR	:=	$(SRC_DIR)/exec
# UTILS_DIR	:=	$(SRC_DIR)/utils

# # Lib
# LIBFT		:=	$(LIBFT_DIR)/libft.a

# # Colors
# DEF_COLOR	:=	\033[0;39m
# GREEN 		:=	\033[0;92m
# CYAN 		:=	\033[0;96m

# INITS		:=	$(INIT_DIR)/init.c \
# 				$(INIT_DIR)/env_utils2.c \
# 				$(INIT_DIR)/env.c

# LEXERS		:=	$(LEXER_DIR)/errors.c \
# 				$(LEXER_DIR)/expand_utils2.c \
# 				$(LEXER_DIR)/expand_utils.c \
# 				$(LEXER_DIR)/expand.c \
# 				$(LEXER_DIR)/lexer.c \
# 				$(LEXER_DIR)/token_check_utils.c \
# 				$(LEXER_DIR)/token_check.c \
# 				$(LEXER_DIR)/token.c

# PARSERS		:=	$(PARSER_DIR)/args.c \
# 				$(PARSER_DIR)/infile.c \
# 				$(PARSER_DIR)/outfile.c \
# 				$(PARSER_DIR)/parser_utils.c \
# 				$(PARSER_DIR)/parser.c

# EXECS		:=	$(EXEC_DIR)/builtins.c \
# 				$(EXEC_DIR)/env_utils.c \
# 				$(EXEC_DIR)/exec_utils.c \
# 				$(EXEC_DIR)/exec_utils2.c \
# 				$(EXEC_DIR)/exec.c \
# 				$(EXEC_DIR)/ft_cd.c \
# 				$(EXEC_DIR)/ft_echo.c \
# 				$(EXEC_DIR)/ft_exit.c \
# 				$(EXEC_DIR)/ft_export_utils.c \
# 				$(EXEC_DIR)/ft_export_utils2.c \
# 				$(EXEC_DIR)/ft_export_utils3.c \
# 				$(EXEC_DIR)/ft_export.c \
# 				$(EXEC_DIR)/hd_count.c \
# 				$(EXEC_DIR)/heredocs_utils.c \
# 				$(EXEC_DIR)/heredocs_utils2.c \
# 				$(EXEC_DIR)/heredocs.c \
# 				$(EXEC_DIR)/multi_cmds.c \
# 				$(EXEC_DIR)/multi_cmds_utils.c \
# 				$(EXEC_DIR)/pipe.c \
# 				$(EXEC_DIR)/single_cmd_builtin.c \
# 				$(EXEC_DIR)/single_cmd.c \
# 				$(EXEC_DIR)/get_redirs.c

# UTILS		:=	$(UTILS_DIR)/free_utils.c \
# 				$(UTILS_DIR)/free.c \
# 				$(UTILS_DIR)/utils.c \
# 				$(UTILS_DIR)/utils2.c \
# 				$(UTILS_DIR)/utils3.c

# SRC			:=	$(SRC_DIR)/main.c $(INITS) $(LEXERS) \
# 				$(PARSERS) $(EXECS) $(UTILS)
# OBJ			:=	$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# # Default make
# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ)
# 	@$(CC) -I $(INC_DIR) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
# 	@echo "$(GREEN)minishell compiled !$(DEF_COLOR)"

# $(BIN_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# # libft
# $(LIBFT):
# 	@make -C ./libft

# # Clean Objects
# clean:
# 	@make -C ./libft clean
# 	rm -rf $(BIN_DIR)
# 	@echo "$(CYAN)binary files cleaned !$(DEF_COLOR)"

# # Full Clean, Objects and Binaries
# fclean: clean
# 	@make -C ./libft fclean
# 	rm -f $(NAME)
# 	@echo "$(CYAN)exec files cleaned !$(DEF_COLOR)"

# # Remake
# re: fclean $(NAME)
# 	@echo "$(GREEN)Cleaned and rebuilt everything !$(DEF_COLOR)"

# # Norminette
# norm:
# 	@norminette $(SRC) $(INC_DIR)/*.h

# # Valgrind
# val: $(NAME)
# 	@valgrind $(VAL_FLAGS) ./$(NAME)

# # Non-File Targets
# .PHONY:	all clean fclean re norm val