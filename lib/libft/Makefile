# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 15:35:38 by momrane           #+#    #+#              #
#    Updated: 2024/06/27 10:32:09 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Archive name
NAME	:=	libft.a

# Directories
SRC_DIR :=	./src
BIN_DIR :=	./bin
INC_DIR :=	./inc

# Compilation
AR 		:=	ar rcs
CC 		:=	cc
FLAGS 	:=	-Wall -Werror -Wextra
HEADER	:=	$(INC_DIR)/libft.h \
			$(INC_DIR)/get_next_line.h

# Sources
FILES	:=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii \
			ft_isdigit ft_isprint ft_itoa ft_lstadd_back ft_lstadd_front \
			ft_lstclear ft_lstdelone ft_lstiter ft_lstlast ft_lstmap \
			ft_lstnew ft_lstsize ft_memchr ft_memcmp ft_memcpy ft_memmove \
			ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
			ft_split ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat \
			ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr \
			ft_strtrim ft_substr ft_tolower ft_toupper get_next_line

SRC		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))

# Binaries
OBJ 	:=	$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

# Default make
all: $(NAME)

# Creating archive
$(NAME): $(OBJ)
	@$(AR) $@ $^

# Linking
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

# Clean binaries
clean:
	@rm -rf $(BIN_DIR)

# Clean binaries and libraries
fclean: clean
	@rm -rf $(NAME)

# remake
re: fclean all

.PHONY: all clean fclean re
