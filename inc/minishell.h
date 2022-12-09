/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/09 03:12:57 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

int	g_status;//exit status

typedef struct	s_sh
{
	t_list	*cmds;//lista de nodes t_cmd, novo node a cada pipe
	char	**envp;//duplicado de **envp
}				t_sh;

typedef struct	s_cmd
{
	char	**args;//comando e argumentos
	char	*path;//path do comando a executar se nao for builtin
	int		in;//default se nao houver redirect/pipe
	int		out;//default se nao houver redirect/pipe
}				t_cmd;

//builtins.c test args
int		ft_pwd(void);
int		ft_unset(t_sh *sh, char **test);

//export.c test args
int		ft_export(t_sh *sh, char **test);
int		print_export(t_sh *sh);
char	**set_export(t_sh *sh);
int		ft_strichr(char *str, char c);
int		ft_strcmp(const char *s1, const char *s2);

//env.c
int		ft_env(t_sh *sh);
char	*get_env(char *var, t_sh *sh);
int		pos_env(char *var, char **envp);
void	set_env(char *var, char *value, t_sh *sh);
void	rmv_env(char *var, t_sh *sh);

//mtr.c
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
//tests
void	test(char **argv, t_sh *sh);

#endif
