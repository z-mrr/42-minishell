/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 17:28:45 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../include/color.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

extern int	g_status;//exit status

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

typedef struct s_sh {
	t_cmd	*cmds;
	t_token *token;
	char	**test;
	char	**envp;
	int	last_pid;
	char	*str;
	int	pos;
	int	wd_begin;
} t_sh;

void	tests(t_sh *sh);
//sortInput.c
void	sortInput(t_sh *f);
void	lexer(t_sh *f);
void	lexer2(t_sh *f);
void	parser(t_sh *f);

//createWords.c //tokenizes the words
void	createWords(t_sh *f);
void	lexQuote(t_sh *f);
void	lexWdend(t_sh *f);
void	lexOp(t_sh *f);
int	findOperator(char c);

//lexer.c

//lexer_utils.c
void	rmvQuotes(t_sh *f);
int	countPairs(char *s);

//parser.c
int     charArrayLen(char **array);
void    addStrCmd(t_cmd *node, char *s);
void    ddl_append(t_cmd *last);
void	initCmd(t_cmd *node);

//ddl_utils.c
void	append_dll(t_sh *f, t_token **head, char *s);
void	addType_ll(t_sh *f, char type);
void 	append_dll_cmd(t_sh *f, t_cmd **head);
void	printList(t_token *head);
void	printListCmd(t_cmd *head);
void	remove_dll(t_sh *f);

//free.c
void	freeTokens(t_sh *f);
//pwd_unset_echo_cd.c test args
int		ft_pwd(void);
int		ft_unset(t_sh *sh);
int		ft_echo(t_sh *sh);
int		ft_cd(t_sh *sht);
int		cd_home(t_sh *sh);

//export_exit.c test args
int		ft_export(t_sh *sh);
int		print_export(t_sh *sh);
char	**set_export(t_sh *sh);
int		ft_exit(t_sh *sh);
void	exit_check(char **str);

//env.c
int		ft_env(t_sh *sh);
char	*get_env(char *var, t_sh *sh);
int		pos_env(char *var, char **envp);
void	set_env(char *var, char *value, t_sh *sh);
void	rmv_env(char *var, t_sh *sh);

//utils.c
int		ft_strichr(char *str, char c);

//mtr_utils.c
int		mtr_len(char **m);
void	mtr_free(char **m);
char	**mtr_dup(char **m);
char	**mtr_rmv(int pos, char **old);
char	**mtr_add(char *str, char **old);

//readline.c
char	*get_str(t_sh *sh);
char	*get_prompt(t_sh *sh);
char	*get_user(void);
char	*get_dir(t_sh *sh);

//signal.c
void	sig_handler(int signal);
void	handle_sig(void);

//main.c
void	shlvl(t_sh *sh);
void	init_sh(int argc, char **argv, char **envp, t_sh *sh);

#endif
