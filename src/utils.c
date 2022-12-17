
#include "../inc/minishell.h"

void	exiting(t_sh *sh)
{
	char	**exit_cmd;
	t_cmd	cmd;

	exit_cmd = malloc(sizeof(char *) * 3);
	exit_cmd[0] = ft_strdup("exit");
	exit_cmd[1] = ft_itoa(g_status);
	exit_cmd[2] = NULL;
	cmd.full_cmd = exit_cmd;
	clear_history();
	free_all(sh);
	ft_exit(&cmd);
}

int	is_dir(char *path)
{
	DIR	*dir;
	int	ret;

	if (!path)
		return (0);
	ret = 0;
	dir = opendir(path);
	if (dir)
		ret = 1;
	closedir(dir);
	return (ret);
}

/*returna primeiro index de char na string*/
int	ft_strichr(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while(str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (c == '\0')
		return (i);
	return (-1);
}

/*compara strings*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	n;
	int	len[2];

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (len[0] > len[1])
		n = len[0];
	else
		n = len[1];
	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		i--;
	return (s1[i] - s2[i]);
}
