/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/06 16:04:43 by gde-alme         ###   ########.fr       */
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
	char		*token_type;
	struct	s_token	*next;
	struct	s_token *prev;
} t_token;

typedef struct s_frame {
	t_token *token;
} t_frame;

//lexer.c
void	printList(t_token *head);
void	free_ll(t_token *head);
void append_ll(t_token **head, char *s);
int	next_quote(char *s, int pos);
int	lexer(char *s);
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
