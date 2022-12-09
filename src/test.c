#include "minishell.h"

void	tests(t_sh *sh)
{
	t_pwd();
	t_export_args(sh);
	t_export_noargs(sh);
	t_unset(sh);
	t_env(sh);

}

void	t_export_args(t_sh *sh)
{
	char	**test;

	test = malloc(sizeof(char *) * 3);
	test[0] = ft_strdup("export");
	test[1] = ft_strdup("a=5");
	test[2] = NULL;
	ft_export(sh, test);
	printf("\n\texport a=5\n\n");
	mtr_free(test);
}

void	t_export_noargs(t_sh *sh)
{
	char	**test;

	test = malloc(sizeof(char *) * 3);
	test[0] = ft_strdup("export");
	test[1] = NULL;
	printf("\n\texport\n\n");
	ft_export(sh, test);
	printf("\n");
	mtr_free(test);

}

void	t_env(t_sh *sh)
{
	printf("\n\tenv\n\n");
	ft_env(sh);
	printf("\n");
}

void	t_pwd()
{
	printf("\n\tpwd\n\n");
	ft_pwd();
	printf("\n");
}

void	t_unset(t_sh *sh)
{
	char **test;

	test=malloc(sizeof(char *) * 4);
	test[0]= ft_strdup("unset");
	test[1]= ft_strdup("b");
	test[2]= ft_strdup("a");
	test[3]= NULL;
	ft_unset(sh, test);
	printf("\n\tunset a\n\n");
	mtr_free(test);
}
