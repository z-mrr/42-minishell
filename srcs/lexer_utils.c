#include "../include/minishell.h"

void	handleDollar(t_frame *f)
{
	int	dollar;
	t_token *node;
	char	*tmp;
	char	*expand;
	char	*tmp2;

	node = f->token;
	dollar = f->pos;
	tmp = NULL;
	if (f->pos - f->wd_begin)
		tmp = ft_substr(node->token_str, f->wd_begin, (f->pos) - f->wd_begin);
	printf("pos: %i - char: %c\n", f->pos, node->token_str[f->pos]);
	f->pos++;
	if (node->token_str[f->pos] == '?')
	{
		f->pos++;
		if (tmp)
			tmp2 = ft_strjoin(tmp, ft_itoa(f->last_pid));
		else
			tmp2 = ft_strdup(ft_itoa(f->last_pid));
	}
	else
	{
	while (node->token_str[f->pos] != '\"' && node->token_str[f->pos] != ' ' && node->token_str[f->pos] != '$' && node->token_str[f->pos])
		f->pos++;
	if (tmp)
	{
		if (ft_strlen(ft_substr(node->token_str, dollar, f->pos - dollar)) < 2)
			{printf("siga\n");exit(-1);}
		tmp2 = ft_strjoin(tmp, getenv("USER"/*ft_substr(node->token_str, dollar, f->pos - dollar)*/));
		free(tmp);
	}
	else
	{
		if (ft_strlen(ft_substr(node->token_str, dollar, f->pos - dollar)) < 2)
			{printf("siga\n");exit(-1);}
		tmp2 = ft_strdup(getenv("USER")); //se n encontrar match, tmp2 = ""
	}
	}
	expand = ft_substr(node->token_str, f->pos, ft_strlen(node->token_str) - f->pos);
	free(node->token_str);
	node->token_str = ft_strjoin(tmp2, expand);
	free(tmp2);
	free(expand);
	printf("expand$: %s\n", node->token_str);
}

/*
void	handleEqual(t_frame *f)
{
	char	*esq;
	char	*dir;
	t_token	*node;

	node = f->token;
	esq = ft_substr(node->token_str, f->wd_begin, f->pos - f->wd_begin);
	f->pos++;
	dir = ft_substr(node->token_str, f->pos, ft_strlen(node->token_str) - f->pos);
	printf("esq: %s\n", esq);
	printf("dir: %s\n", dir);
	//adicionar as var;
}
*/

int	countPairs(char *s)
{
	int	i;
	int	pairs;
	char	c;

	i = 0;
	pairs = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
		{
			c = s[i];
			i++;
			pairs++;
			while (s[i] != c)
				i++;
		}
		i++;
	}
	return (pairs);
}

void	rmvQuotes(t_frame *f)
{
	int	i;
	int	j;
	char c;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ((ft_strlen(f->token->token_str) - (countPairs(f->token->token_str) * 2) + 1)));
	while (f->token->token_str[i] != '\0')
	{
		if (f->token->token_str[i] == 34 || f->token->token_str[i] == 39)
		{
			c = f->token->token_str[i];
			i++;
			while (f->token->token_str[i] != c)
			{
				new_str[j] = f->token->token_str[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			new_str[j] = f->token->token_str[i];
			i++;
			j++;
		}
	}
	free(f->token->token_str);
	new_str[j] = '\0';
	f->token->token_str = new_str;
}

/* lida com '$' e '=' */
void	tokenizeWord(t_frame *f)
{
	t_token *node;

	node = f->token;
	f->pos = 0;
	f->wd_begin = 0;
	/*if (ft_strlen(node->token_str) < 2 && node->token_str[0] == '$')
		return ;*/
	while (node->token_str[f->pos])
	{
		//dentro de '' passa so a frente;
		if (node->token_str[f->pos] == 39)
		{
			f->pos++;
			printf("dentro de \' \n");
			while (node->token_str[f->pos] != 39)
				f->pos++;
			f->pos++;
		}
		//se dentro de aspas:
			// '$' //pega na palavra a direita para com aspas ou final de palavra; retira a var e insere o value; se n der match delete_ll
		else if (node->token_str[f->pos] == 34)
		{
			f->pos++;
			printf("fora de \" \n");
			while (node->token_str[f->pos] != 34 && node->token_str[f->pos])
			{
				if (node->token_str[f->pos] == '$')
				{
					handleDollar(f);
					f->pos++;
				}
				else
					f->pos++;
			}
			f->pos++;
		}
		//se fora de aspas:
			// '$' //palavra a direita para com aspas ou final de palavra;
		else if (node->token_str[f->pos] == '$')
		{
			handleDollar(f);
			//f->pos++;
		}
		// '=' // se var nao tiver aspas: adiciona a var com valor value a uma **vars, remove token; se var tiver aspas, n faz nada
		/*else if (node->token_str[f->pos] == '=' && node->prev == NULL)
			handleEqual(f); */
		else
			f->pos++;
	}
	rmvQuotes(f);
}
