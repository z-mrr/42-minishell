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
		while (node->token_str[f->pos] != '\"' && node->token_str[f->pos] != ' ' && node->token_str[f->pos] != '$' && node->token_str[f->pos] != '\'' && node->token_str[f->pos])
			f->pos++;
		if (tmp)
		{
			if (ft_strlen(ft_substr(node->token_str, dollar, f->pos - dollar)) < 2)
				tmp2 = ft_strjoin(tmp, "$");
			else
				tmp2 = ft_strjoin(tmp, getenv("USER"/*ft_substr(node->token_str, dollar, f->pos - dollar)*/));
			free(tmp);
		}
		else
		{
			if (ft_strlen(ft_substr(node->token_str, dollar, f->pos - dollar)) < 2)
				tmp2 = ft_strdup("$");
			else
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
			c = f->token->token_str[i++];
			while (f->token->token_str[i] != c)
				new_str[j++] = f->token->token_str[i++];
			i++;
		}
		else
			new_str[j++] = f->token->token_str[i++];
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
	while (node->token_str[f->pos])
	{
		if (node->token_str[f->pos] == 39) /* dentro de '' passa so a frente; */
		{
			f->pos++;
			printf("dentro de \' \n");
			while (node->token_str[f->pos] != 39)
				f->pos++;
			f->pos++;
		}
		else if (node->token_str[f->pos] == 34) /* SE DENTRO DE ASPAS E $; palavra a direita para com aspas ou final de palavra; expand p seu valor ou para nada */
		{
			f->pos++;
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
		else if (node->token_str[f->pos] == '$') /* SE FORA DE ASPAS E $; palavra a direita para com aspas ou final de palavra */
		{
			handleDollar(f);
			//f->pos++;
		}
		else
			f->pos++;
	}
	rmvQuotes(f);
}
