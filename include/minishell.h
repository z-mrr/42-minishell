/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/04 15:21:26 by gde-alme         ###   ########.fr       */
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
	char		*token_type;
	struct	s_token	*next;
} t_token;

typedef struct s_frame {
	struct	s_token *token_f;
} t_frame;

//lexer.c
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
