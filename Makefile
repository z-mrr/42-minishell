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

READLINE_DIR =	/usr/include/readline

OBJ =			$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

INC =			-I$(INC_DIR) -I$(LIBFT_DIR) -I$(READLINE_DIR)

LIBFT =			libft/libft.a

LINK =			-L$(LIBFT_DIR) -lft -L$(READLINE_DIR) -lreadline

CC =			gcc

CFLAGS =		-Wall -Werror -Wextra

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $(<) -o $(@)

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(NAME):		$(LIBFT) $(OBJ_DIR) $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) $(LINK)

$(LIBFT):
				make bonus -s -C $(LIBFT_DIR)

clean:
				make clean -s -C $(LIBFT_DIR)
				rm -f $(OBJ)

fclean:			clean
				make fclean -s -C $(LIBFT_DIR)
				rm -rf $(OBJ_DIR) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
