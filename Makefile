# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 13:13:31 by jdias-mo          #+#    #+#              #
#    Updated: 2022/12/02 21:04:25 by jdias-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INC_DIR		=	inc
LIBFT_DIR	=	libft
BUILD_DIR	=	build
SRC_DIR		=	src
OBJ_DIR		=	$(BUILD_DIR)/objects

SRC		=	$(SRC_DIR)/*.c

ifeq ($(shell uname), Linux)
	READLINE_DIR	=	/usr/include/readline
else
	READLINE_DIR	=	~/.brew/opt/readline/lib
endif

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(READLINE_DIR)
LINKS		=	-L$(LIBFT_DIR) -lft -L$(READLINE_DIR) -lreadline

all: mklibft $(BUILD_DIR) $(NAME)

readline:
	@../libreadline.sh

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(INCLUDES) $(^) -o $(@) $(LINKS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)

mklibft:
	@make -s -C $(LIBFT_DIR)

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(BUILD_DIR)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

e: re
	@./minishell

.PHONY: all clean fclean re bonus
