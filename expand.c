#include "../include/minishell.h"

/* devolve pos do final da $var */
int	endVarPos(char *s, int pos)
{
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == 34 || s[pos] == 39 || s[pos] == ' ' || s[pos] == '?')
			return (pos);
		pos++;
	}
	return (i);
}

/* devolve expansao ou null */
char	*getExpansion(char *s)
{
	if (!(ft_strcmp(s, "$?")))
		return (s);
	else if (!(ft_strcmp(s, "$$")))
		return (s);
	else if (!(ft_strcmp(s, "$")))
		return (s);
	else
	{
		free(s);
		/* get_env */ return (NULL);
	}

}

char	*newStr(char *old_str, int pos, char **new_str)
{
	char	*expansion;
	char	*tmp;

	expansion = NULL;
	tmp = NULL;
	expansion = getExpansion(ft_substr(old_str, pos,  endVarPos(old_str, pos + 1) - pos)); /* devolve respectiva expansao; */
	if (new_str) /* se ja foi lido alguma coisa, adiciona expansao*/
	{
		tmp = ft_strdup(*new_str);
		free(new_str);
		new_str = ft_strjoin(tmp, expansion);
	}
	else /*se ainda n foi nada lido */
	{
		tmp = ft_substr(old_str, 0, pos - 1);
		new_str = ft_strjoin(tmp, expansion);
	}
	free(expansion);
	free(tmp);
	return (new_str);
}

/* recebe uma str,  expande todos os $ */
void	expanStr(char **old_str, int pos)
{
	char	*tmp;

	new_str = NULL;
	tmp = NULL;
	while (old_str[pos])
	{
		if (old_str[pos] == '$' && old_str[pos + 1] != '\0') /* se encontrar $ e nao for o ultimo */
		{
			_newStr(old_str, pos, &new_str);
			pos = endVarPos(old_str, pos) + 1; /* nova pos no final do que foi lido */
		}
		else
			pos ++
	}
}

/* token a token , expande os $ na str*/
void	expander(t_sh *f)
{
	t_token *node;

	node = NULL;
	node = f->token
	while (token != NULL)
	{
		expandStr(node->token_str, 0);
		//if (node->token_str == '\0') ; remove node.
		node = node->next;
	}
}

void	sortInput(t_sh *f)
{
	createWords(f); /* separa palaras de operadores */
	expander(f); /* expande $ */
	parser(f); /* cria cmds com as palavras e operadores*/
	freeTokens;
}
