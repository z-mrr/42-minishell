/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/11 06:00:58 by gde-alme         ###   ########.fr       */
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
	char		*token_str;
	char		token_type;
	struct	s_token	*next;
	struct	s_token *prev;
} t_token;

typedef	struct	s_cmd {
	char	**full_cmd; //cmd e args
	char	*path; //cmd PATH; se builtin deixar so nome
	int	in_fd;
	int	out_fd;
	int	err_fd;
	struct s_cmd *next;
	struct s_cmd *prev;
} t_cmd;

typedef struct s_frame {
	t_cmd	*cmds;
	t_token *token;
	char	**envp;
	int	last_pid;
	char	*str;
	char	*new_str;
	int	pos;
	int	wd_begin;
	char	c;
} t_frame;

//sortInput.c
void	sortInput(t_frame *f);
void	createWords(t_frame *f);
int	lexer(t_frame *f);
void	lexer2(t_frame *f);
void	parser(t_frame *f);

//createWords.c //tokenizes the words
void	lexQuote(t_frame *f);
void	lexWdend(t_frame *f);
void	lexOp(t_frame *f);
int	findOperator(char c);

//lexel.c

//lexer_utils.c
void	rmvQuotes(t_frame *f);
int	countPairs(char *s);

//parser.c
void	parsePipes(t_frame *f);
void	addStrCmd(t_frame *f);
int	charArrayLen(char **array);

//ddl_utils.c
void append_dll(t_frame *f, t_token **head, char *s);
void	addType_ll(t_frame *f, char type);
void append_dll_cmd(t_frame *f, t_cmd **head);
void	free_dll(t_frame *f);
void	printList(t_token *head);
void	remove_dll(t_frame *f);

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
