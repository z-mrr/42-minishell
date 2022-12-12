#include "../include/minishell.h"

void	tests(t_sh *sh);
void	t_unset(t_sh *sh);
void	t_pwd();
void	t_env(t_sh *sh);
void	t_export_noargs(t_sh *sh);
void	t_export_args(t_sh *sh);
void	t_echo(t_sh *sh);
void	t_echo_n(t_sh *sh);
void	t_cd(t_sh *sh);
void	t_cd_noargs(t_sh *sh);
void	t_exit(t_sh *sh);
void	t_exit_arg(t_sh *sh);
void	t_exit_bad(t_sh *sh);

void	tests(t_sh *sh)
{
	t_pwd();
	t_cd(sh);
	t_pwd();
	t_cd_noargs(sh);
	t_pwd();
	t_export_args(sh);
	t_export_noargs(sh);
	t_unset(sh);
	t_env(sh);
	t_echo(sh);
	t_echo_n(sh);
	t_exit_bad(sh);
//	t_exit_arg(sh);
//	t_exit(sh);
}

void	t_exit(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 2);
	sh->test[0] = ft_strdup("exit");
	sh->test[1] = NULL;
	ft_exit(sh);
	printf("\n___________________exit no args___________________\n");
	mtr_free(sh->test);
}

void	t_exit_arg(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 3);
	sh->test[0] = ft_strdup("exit");
	sh->test[1] = ft_strdup("      -20");
	sh->test[2] = NULL;
	ft_exit(sh);
	printf("\n___________________exit args___________________\n");
	mtr_free(sh->test);
}

void	t_exit_bad(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 3);
	sh->test[0] = ft_strdup("exit");
	sh->test[1] = ft_strdup("      --20");
	sh->test[2] = NULL;
	ft_exit(sh);
	printf("\n___________________exit invalid args___________________\n");
	mtr_free(sh->test);
}

void	t_cd_noargs(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 2);
	sh->test[0] = ft_strdup("cd");
	sh->test[1] = NULL;
	ft_cd(sh);
	printf("\n___________________cd no args___________________\n");
	mtr_free(sh->test);
}

void	t_cd(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 3);
	sh->test[0] = ft_strdup("cd");
	sh->test[1] = ft_strdup("../libft");
	sh->test[2] = NULL;
	ft_cd(sh);
	printf("\n___________________cd args___________________\n");
	mtr_free(sh->test);
}

void	t_echo(t_sh *sh)
{
	sh->test=malloc(sizeof(char *) * 4);
	sh->test[0]= ft_strdup("echo");
	sh->test[1]= ft_strdup("a");
	sh->test[2]= ft_strdup("asdasdasd");
	sh->test[3]= NULL;
	printf("\n___________________echo___________________\n");
	ft_echo(sh);
	mtr_free(sh->test);
}

void	t_echo_n(t_sh *sh)
{
	sh->test=malloc(sizeof(char *) * 5);
	sh->test[0]= ft_strdup("echo");
	sh->test[1]= ft_strdup("-n");
	sh->test[2]= ft_strdup("asdasdasd");
	sh->test[3]= ft_strdup("asdasdasd");
	sh->test[4]= NULL;
	printf("\n___________________echo -n___________________\n");
	ft_echo(sh);
	mtr_free(sh->test);
}

void	t_export_args(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 3);
	sh->test[0] = ft_strdup("export");
	sh->test[1] = ft_strdup("a=5");
	sh->test[2] = NULL;
	ft_export(sh);
	printf("\n___________________export a=5___________________\n");
	mtr_free(sh->test);
}

void	t_export_noargs(t_sh *sh)
{
	sh->test = malloc(sizeof(char *) * 3);
	sh->test[0] = ft_strdup("export");
	sh->test[1] = NULL;
	printf("\n___________________export___________________\n");
	ft_export(sh);
	mtr_free(sh->test);

}

void	t_env(t_sh *sh)
{
	printf("\n___________________env___________________\n");
	ft_env(sh);
}

void	t_pwd()
{
	printf("\n___________________pwd___________________\n");
	ft_pwd();
}

void	t_unset(t_sh *sh)
{
	sh->test=malloc(sizeof(char *) * 4);
	sh->test[0]= ft_strdup("unset");
	sh->test[1]= ft_strdup("b");
	sh->test[2]= ft_strdup("a");
	sh->test[3]= NULL;
	ft_unset(sh);
	printf("\n___________________unset a___________________\n");
	mtr_free(sh->test);
}
