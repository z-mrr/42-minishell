# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:02:01 by jdias-mo          #+#    #+#              #
#    Updated: 2023/01/09 19:44:50 by jdias-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

SRC =			$(addsuffix .c, bi_cd \
								bi_exit \
								bi_export \
								bi_pwd_unset_echo \
								create_words \
								dll_utils \
								env \
								error \
								exec \
								expand_utils \
								expand \
								fork \
								free \
								heredoc \
								lexer_utils \
								main \
								mtr_utils \
								parser \
								readline \
								redir_utils \
								redirecs \
								sort_input \
								utils \
								)

INC_DIR =		inc/

SRC_DIR =		src/

OBJ_DIR =		obj/

LIBFT_DIR =		libft/

READLINE_DIR =	/usr/include/readline/

OBJ =			$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

INC =			-I$(INC_DIR) -I$(LIBFT_DIR)inc -I$(READLINE_DIR)

LIBFT =			libft/libft.a

LINK =			-L$(LIBFT_DIR) -L$(READLINE_DIR)

LIB =			-lft -lreadline

CC =			gcc

CFLAGS =		-Wall -Werror -Wextra

RM =			rm -f

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $(<) -o $(@) $(INC)

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(NAME):		$(LIBFT) $(OBJ_DIR) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINK) $(LIB)

$(LIBFT):
				make bonus -C $(LIBFT_DIR)

clean:
				make clean -C $(LIBFT_DIR)
				$(RM) $(OBJ) -r $(OBJ_DIR)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
