/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/17 19:36:48 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/color.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BUFFER_SIZE 4096 //MAX_PATH =~4096 bytes
# define READ 0
# define WRITE 1

extern int	g_status;//exit status. When a script ends with an exit that has no parameter, the exit status of the script is the exit status of the last command executed in the script (previous to the exit). expand $?

typedef struct	s_token
{
	char			*token_str;
	char			token_type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef	struct	s_cmd
{
	char			**full_cmd; //cmd e args
	char			*path; //cmd PATH
	int				in_file;
	int				out_file;
	struct s_cmd	*next;
	struct s_cmd	*prev;//Nao pode ser simples?
}				t_cmd;

typedef struct	s_parser
{
	char	*str;
	int		pos;
	int		wd_begin;
}				t_parser;

typedef struct	s_sh
{
	t_cmd		*cmd;
	t_token		*token;
	t_parser	*parser;
	char		**envp;
}				t_sh;

//fork.c
void	child_fd(t_cmd *cmd, int *fd);
void	ft_fork(t_sh *sh, t_cmd *cmd, int *fd);
int		check_fork(t_sh *sh, t_cmd *cmd, int *fd);

//exec.c
void	parent_fd(t_cmd *cmd, int *fd);
char	*get_path(t_sh *sh, t_cmd *cmd);
void	execInput(t_sh *sh);
int		ft_builtin(t_sh *sh, t_cmd *cmd);
int		check_builtin(t_cmd *cmd);

//sortInput.c
int		sortInput(t_sh *f);

//createWords.c //tokenizes the words
int		createWords(t_sh *f);
int		lexQuote(t_sh *f);
void	lexWdend(t_sh *f);
void	lexOp(t_sh *f);
int		findOperator(char c);

//lexer.c
void	lexer(t_sh *f);
int    _expander(t_sh *f);

//lexer_utils.c
void	rmvQuotes(t_token *node);
int		countPairs(char *s);
void	ddl_removeToken(t_token **head, t_token *node);
int		_endVarPos(char *s, int pos);

//parser.c
int     charArrayLen(char **array);
void    addStrCmd(t_cmd *node, char *s);
void    ddl_append(t_cmd **head);
void	initCmd(t_cmd *node);
int		parsecmd(t_sh *f);

//ddl_utils.c
void	append_dll(t_sh *f, t_token **head, char *s);/*f nao é usado*/
void	addType_ll(t_sh *f, char type);
void	printList(t_token *head);
void	printListCmd(t_cmd *head);

//free.c
void	free_all(t_sh *sh);
void	free_token(t_sh *f);
void	free_cmd(t_sh *sh);

//error.c
int		parserError(t_sh *f, char *error);

//redirecs.c
int		parse_redirecs(t_sh *f, t_cmd *node, t_token *token);

//redir_utils.c
int		redirecOutFile(char *pathname, t_cmd *node, t_token *token);
char	*get_filepath(t_sh *f, t_token *token);
char	*get_filepathname(char *path, t_token *token);

//pwd_unset_echo_cd.c test args
int		ft_pwd(void);
int		ft_unset(t_sh *sh, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_sh *sh, t_cmd *cmd);
int		cd_home(t_sh *sh, t_cmd *cmd);

//export_exit.c test args
int		ft_export(t_sh *sh, t_cmd *cmd);
int		print_export(t_sh *sh);
char	**set_export(t_sh *sh);
int		ft_exit(t_cmd *cmd);
void	exit_check(char **str);

//env.c
int		ft_env(t_sh *sh);
char	*get_env(char *var, t_sh *sh);
int		pos_env(char *var, char **envp);
void	set_env(char *var, char *value, t_sh *sh);
void	rmv_env(char *var, t_sh *sh);

//utils.c
int		ft_strichr(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		is_dir(char *path);
void	exiting(t_sh *sh);

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
void	init_sh(t_sh *sh, char** envp);
void	init_parser(t_sh *sh);
void	shlvl(t_sh *sh);
void	init(int argc, char **argv, char **envp, t_sh *sh);

#endif
