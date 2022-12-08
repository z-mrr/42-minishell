/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/08 03:16:48 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define SYNTAX_ERR "-minishell: syntax error near unexpected token"

typedef struct s_token {
	int		token_id;
	char		*token_str;
	char		token_type;
	struct	s_token	*next;
	struct	s_token *prev;
} t_token;

typedef struct s_frame {
	t_token *token;
	char	**envp;
	char	*str;
	char	*new_str;
	int	pos;
	int	wd_begin;
	char	c;
} t_frame;

//ddl_utils.c 
void	printList(t_token *head);
void	free_ll(t_token *head);
void	addType_ll(t_frame *f, char type);
void	insert_ll(t_token **head, char *s);
void	append_ll(t_frame *f, t_token **head, char *s);

//lexer_utils.c
void	tokenizeWord(t_frame *f);
void	twEqual(t_frame *f, t_token *head);
int	checkqts(char *s);
//tokenize_utlis.c
int	findOperator(char c);
void	lexWdend(t_frame *f);
void	lexOp(t_frame *f);
void	lexQuote(t_frame *f);
//tokenizer.c
void	lexer(t_frame *f);
void	tokenizer(t_frame *f);
//readline.c
char	*get_str(void);
char	*resolve_str(char	*line);
char	*get_prompt(void);
//signal.c
void sig_handler(int signal);
void handle_sig();
//main.c"
void handle_sig();
void sig_handler(int signal);

#endif
