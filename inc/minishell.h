/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:43:06 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "color.h"
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
# include <errno.h>
# include <sys/ioctl.h>

# define READ 0
# define WRITE 1

extern int	g_status;

typedef struct s_token
{
	char			*word;
	char			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**full_cmd;
	char			*path;
	int				in_file;
	int				out_file;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_parser
{
	char	*str;
	int		pos;
	int		wd_b;
}	t_parser;

typedef struct s_sh
{
	t_cmd		*cmd;
	t_token		*token;
	t_parser	*parser;
	char		**envp;
	int			i;
	int			fork;
	pid_t		pid;
}	t_sh;

//fork.c
void	child_fd(t_cmd *cmd, int *fd);
void	ft_fork(t_sh *sh, t_cmd *cmd, int *fd);
int		check_fork(t_sh *sh, t_cmd *cmd, int *fd);

//exec.c
void	parent_fd(t_cmd *cmd, int *fd);
char	*get_path(t_sh *sh, t_cmd *cmd);
int		exec_input(t_sh *sh);
int		ft_builtin(t_sh *sh, t_cmd *cmd);
int		check_builtin(t_cmd *cmd);

//sort_input.c
int		sort_input(t_sh *f);

//create_words.c //tokenizes the words
int		create_words(t_sh *f);
int		lex_quote(t_sh *f);
void	lex_wdend(t_sh *f);
void	lex_op(t_sh *f);
int		find_operator(char c);

//lexer.c
void	lexer(t_sh *f);
int		_expander(t_sh *f);

//lexer_utils.c
void	rmv_quotes(t_token *node);
int		count_pairs(char *s);
void	ddl_remove_token(t_token **head, t_token *node);
int		end_varpos(char *s, int pos);

//parser.c
int		char_arraylen(char **array);
void	addstr_cmd(t_cmd *n, char *s);
void	ddl_append(t_cmd **head);
void	initcmd(t_cmd *node);
int		parsecmd(t_sh *f);

//expand_utils.c
char	*_get_full_rest(t_sh *f, char *old_str);
char	*_get_rest(char *old_str, t_sh *f);
char	*_get_expansion(char *old_str, t_sh *f);

//ddl_utils.c
void	append_dll(t_sh *f, t_token **head, char *s);
void	add_type_ll(t_sh *f, char type);
int		rmv_nodes(t_sh *f);

//free.c
void	free_all(t_sh *sh);
void	free_tokens(t_sh *f);
void	free_cmd(t_sh *sh);

//error.c
int		parser_error(t_sh *f, char *error);
int		p_error(char *s1, char *s2, char *s3, int status);

//redirecs.c
int		parse_redirecs(t_sh *f, t_cmd *node, t_token *token);

//redir_utils.c
int		redirec_outfile(char *pathname, t_cmd *node, t_token *token);
char	*get_filepath(t_sh *f, t_token *token);
char	*get_filepathname(char *path, t_token *token);
int		redirec_infile(char *pathname, t_cmd *node, t_token *token);

//heredoc.c
int		redir_heredoc(t_cmd *node, char *eof);

//bi_pwd_unset_echo_env.c
int		ft_pwd(void);
int		ft_unset(t_sh *sh, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_sh *sh);

//bi_cd.c
int		ft_cd(t_sh *sh, t_cmd *cmd);
int		cd_home(t_sh *sh, t_cmd *cmd);
int		cd_dash(t_sh *sh, t_cmd *cmd);

//bi_export.c
int		ft_export(t_sh *sh, t_cmd *cmd);
void	print_export(t_sh *sh);
char	**set_export(t_sh *sh);
int		export_novalue(t_sh *sh, char *var);

//bi_exit.c
int		ft_exit(t_cmd *cmd);
void	exit_check(char **str);

//env.c
char	*get_env(char *var, t_sh *sh);
int		pos_env(char *var, char **envp);
int		set_env(char *var, char *value, t_sh *sh);
void	rmv_env(char *var, t_sh *sh);

//utils.c
int		ft_strichr(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		is_dir(char *path);
void	ft_wait(t_sh *sh);

//mtr_utils.c
int		mtr_len(char **m);
void	mtr_free(char **m);
char	**mtr_dup(char **m);
char	**mtr_rmv(int pos, char **old);
char	**mtr_add(char *str, char **old);

//readline.c
char	*get_str(t_sh *sh);
char	*get_prompt(t_sh *sh);
char	*get_user(t_sh *sh);
char	*get_dir(t_sh *sh);

//main.c
void	sig_handler(int signal);
int		init(int argc, char **argv, char **envp, t_sh *sh);
void	shlvl(t_sh *sh);
void	oldpwd(t_sh *sh);

#endif
