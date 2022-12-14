#include "../inc/minishell.h"

void	ddl_removeToken(t_token **head, t_token *node)
{
	if (*head == NULL || node == NULL)
		return ;
	if (*head == node)
		*head = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free(node);
}

/* devolve pos do final da $var */
int	_endVarPos(char *s, int pos)
{
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == 34 || s[pos] == 39 || s[pos] == ' ' || s[pos - 1] == '?')
			return (pos);
		pos++;
	}
	return (pos);
}

/* devolve expansao ou null */
char	*_getExpansion(char *old_str, t_sh *f)
{
	char	*expansion;

	expansion = NULL;
	printf("pos: %i, str: %s\n", f->parser->pos, old_str);
	if (_endVarPos(old_str, f->parser->pos + 1) != '$')
		printf("expan: %s\n", expansion = ft_substr(old_str, f->parser->pos,  _endVarPos(old_str, f->parser->pos + 1) - f->parser->pos)); /* devolve respectiva expansao; */
	else
		printf("expan$: %s\n", expansion = ft_substr(old_str, f->parser->pos,  _endVarPos(old_str, f->parser->pos + 1) - 1));

	/*get env*/
	free(expansion);

	return (NULL);
}

char	*_getRest(char *old_str, t_sh *f)
{
	int	start;
	char	*left;

	left = NULL;
	start = f->parser->pos;
	while (old_str[f->parser->pos] != '$' && old_str[f->parser->pos] != '\0')
		f->parser->pos++;
	if (f->parser->pos > start)
	{
		left = ft_substr(old_str, start, f->parser->pos);
		printf("left = %s\n", left);
		return (left);
	}
	else
		return (NULL);
}

char	*_getFullRest(t_sh *f, char *old_str)
{
	char	*frest;
	char	*parsed;
	char	*expansion;

	frest = NULL;
	parsed = _getRest(old_str, f);
	expansion = _getExpansion(old_str, f);
	if (expansion && parsed)
	{
		frest = ft_strjoin(parsed, expansion);
		free(parsed);
		free(expansion);
	}
	else if (parsed)
	{
		frest = ft_strdup(parsed);
		free(parsed);
	}
	else
		return (NULL);
	return (frest);
}


/* recebe uma str,  expande todos os $ */
char	*_expandStr(t_sh *f, char *old_str)
{
	char	*rest;
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	rest = NULL;
	f->parser->pos = 0;
	while (old_str[f->parser->pos])
	{
		printf("rest: %s\n", rest = _getFullRest(f, old_str));
		if (new_str)
		{
			tmp = ft_strdup(new_str);
			free(new_str);
			printf("new_str: %s\n", new_str = ft_strjoin(tmp, rest));
			free(tmp);
		}
		free(rest);
		exit(-1);
		printf("pos: %i\n\n", f->parser->pos = _endVarPos(old_str, f->parser->pos + 1)); /* nova pos no final do que foi lido */
	}
	return (new_str);
}

/* token a token , expande os $ na str*/
void	_expander(t_sh *f)
{
	t_token *node;
	char	*tmp;

	node = NULL;
	node = f->token;
	while (node != NULL)
	{
		if (ft_strchr(node->token_str, '$'))
		{
			tmp = ft_strdup(node->token_str);
			free(node->token_str);
			node->token_str = _expandStr(f, tmp);
			free(tmp);
		}
		if (!(node->token_str))
			{printf("node: %s", node->token_str);exit(-1);}
		//	rmvQuotes(node);
		node = node->next;
	}
}

