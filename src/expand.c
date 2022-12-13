#include "../inc/minishell.h"

/* devolve pos do final da $var */
int	_endVarPos(char *s, int pos)
{
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == 34 || s[pos] == 39 || s[pos] == ' ' || s[pos] == '?')
			return (pos);
		pos++;
	}
	return (pos);
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
		/* get_env */ return (ft_strdup(NULL));
	}

}

char	*_newStr(char *old_str, int pos, char *new_str)
{
	char	*expansion;
	char	*tmp;

	expansion = NULL;
	tmp = NULL;
	expansion = getExpansion(ft_substr(old_str, pos,  _endVarPos(old_str, pos + 1) - pos)); /* devolve respectiva expansao; */
		exit(-1);
	if (new_str) /* se ja foi lido alguma coisa, adiciona expansao*/
	{
		if (expansion)
		{
			tmp = ft_strdup(new_str);
			free(new_str);
			new_str = ft_strjoin(tmp, expansion);
		}
	}
	else /*se ainda n foi nada lido */
	{
		tmp = ft_substr(old_str, 0, pos - 1);
		if (expansion)
			new_str = ft_strjoin(tmp, expansion);
	}
		exit(-1);
	free(expansion);
	free(tmp);
	return (new_str);
}

/* recebe uma str,  expande todos os $ */
char	*_expandStr(char *old_str, int pos)
{
	char	*tmp;
	char	*new_str;

	new_str = NULL;
	tmp = NULL;
	while (old_str[pos])
	{
		if (old_str[pos] == '$' && old_str[pos + 1] != '\0') /* se encontrar $ e nao for o ultimo */
		{
			if (new_str)
			{
				tmp = ft_strdup(new_str);
				free(new_str);
			}
			new_str = _newStr(old_str, pos, tmp);
			pos = _endVarPos(old_str, pos) + 1; /* nova pos no final do que foi lido */
		}
		else
			pos++;
	}
	if (new_str)
		return (new_str);
	else
		return (old_str);
}

/* token a token , expande os $ na str*/
void	_expander(t_sh *f)
{
	t_token *node;

	node = NULL;
	node = f->token;
	while (node != NULL)
	{
		
		printf("%s\n", _expandStr(node->token_str, 0));
		rmvQuotes(node);
		//if (node->token_str == '\0') ; remove node.
		node = node->next;
	}
}
