#include "../include/minishell.h"

int	checkqts(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

// '=' //palavra a esquerda n pode ter aspas; nao pode estar dentro de aspas; se invalido corta bocado
void	twEqual(t_frame *f, t_token *head)
{
	char	*pesq;
	char	*pdir;

	
	pesq = ft_substr(head->token_str, f->wd_begin, f->pos - f->wd_begin);
	f->pos++;
	f->wd_begin = f->pos;
	if (checkqts(pesq))
	{
		printf("pesq: %s\n", pesq);
		printf("pdir: %s\n", pdir);
		free(pesq);
		return ;
	}
	while (head->token_str[f->pos])
		f->pos++;
	pdir = ft_substr(head->token_str, f->wd_begin, f->pos - f->wd_begin);
	free(head->token_str);
	head->token_str = pesq;
	//insert_ll('=')
	//insert_ll(pdir)
	printf("pesq: %s\n", pesq);
	printf("pdir: %s\n", pdir);
	
}

/* lida com '$' e '=' */
void	tokenizeWord(t_frame *f, t_token *head)
{
	f->pos = 0;
	f->wd_begin = 0;
	while (head->token_str[f->pos])
	{
		// '=' //palavra a esquerda n pode ter aspas; nao pode estar dentro de aspas;
		if (head->token_str[f->pos] == '=')
			twEqual(f, head);
		else
			f->pos++;
		// '$' //palavra a dereita para com aspas;
			//$? PID do ultimo running process at end
			//$$ PID da shell
			//se $ ou $kahbekb , corta so este bocado
		//retirar aspas
	}
}
