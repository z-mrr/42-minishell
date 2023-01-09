# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:02:01 by jdias-mo          #+#    #+#              #
#    Updated: 2023/01/09 19:31:07 by jdias-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

SRC =			$(addsuffix .c, ft_isascii \
								ft_isprint \
								ft_isalpha \
								ft_isdigit \
								ft_isalnum \
								ft_tolower \
								ft_toupper \
								ft_strlen \
								ft_strlcpy \
								ft_strlcat \
								ft_strchr \
								ft_strrchr \
								ft_strnstr \
								ft_strncmp \
								ft_atoi \
								ft_memset \
								ft_bzero \
								ft_memcpy \
								ft_memmove \
								ft_striteri \
								ft_memchr \
								ft_memcmp \
								ft_strdup \
								ft_calloc \
								ft_itoa \
								ft_putchar_fd \
								ft_putstr_fd \
								ft_putendl_fd \
								ft_putnbr_fd \
								ft_substr \
								ft_strjoin \
								ft_strtrim \
								ft_split \
								ft_strmapi \
								)

B_SRC =			$(addsuffix .c, ft_lstadd_front \
								ft_lstnew \
								ft_lstsize \
								ft_lstlast \
								ft_lstadd_back \
								ft_lstdelone\
								ft_lstclear \
								ft_lstiter \
								ft_lstmap \
								)

SRC_DIR =		src/

OBJ_DIR =		obj/

INC_DIR =		inc/

INC =			-I$(INC_DIR)

OBJ =			$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

B_OBJ =			$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(B_SRC)))

AR =			ar rcs

CC =			gcc

CFLAGS =		-Wall -Werror -Wextra

RM =			rm -f

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $(<) -o $(@) $(INC)

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(NAME):		$(OBJ_DIR) $(OBJ)
				$(AR) $(NAME) $(OBJ)

bonus:			$(OBJ_DIR) $(OBJ) $(B_OBJ)
				$(AR) $(NAME) $(OBJ) $(B_OBJ)

clean:
				$(RM) $(OBJ) -r $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

rebonus:		fclean bonus

.PHONY:			all clean fclean re bonus rebonus
