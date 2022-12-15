#include "../inc/minishell.h"

/* devolve expansao ou null */
char	*_getExpansion(char *old_str, t_sh *f)
{
	char	*expansion;
	char	*env;

	expansion = NULL;
	env = NULL;
	if (_endVarPos(old_str, f->parser->pos + 1) != '$')
		expansion = ft_substr(old_str, f->parser->pos,  _endVarPos(old_str, f->parser->pos + 1) - f->parser->pos);
	else
		expansion = ft_substr(old_str, f->parser->pos,  _endVarPos(old_str, f->parser->pos + 1) - 1);
	if (!(ft_strcmp(expansion, "$?")))
		return (ft_strdup("0"));
	if (!(ft_strcmp(expansion, "$")))
		return (expansion);
	env = get_env(expansion + 1, f);
	free(expansion);
	if (env)
		return (env);
	return (NULL);
}

char	*_getRest(char *old_str, t_sh *f)
{
	int	start;
	char	*left;

	left = NULL;
	start = f->parser->pos;
	while (old_str[f->parser->pos] != '\0' && old_str[f->parser->pos] != '$')
	{
		if (old_str[f->parser->pos] == 39)
		{
			f->parser->pos++;
			while (old_str[f->parser->pos] != 39)
				f->parser->pos++;
			f->parser->pos++;
		}
		else
			f->parser->pos++;
	}
	if (f->parser->pos > start)
	{
		left = ft_substr(old_str, start, f->parser->pos - start);
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
	else if (expansion)
	{
		frest = ft_strdup(expansion);
		free(expansion);
	}
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
		rest = _getFullRest(f, old_str);
		if (rest)
		{
			if (new_str)
			{
				tmp = ft_strdup(new_str);
				free(new_str);
				new_str = ft_strjoin(tmp, rest);
				free(tmp);
				free(rest);
			}
			else
				new_str = ft_strdup(rest);
		}
		f->parser->pos = _endVarPos(old_str, f->parser->pos + 1);
	}
	free(rest);
	return (new_str);
}


/* remove nodes */
int	rmvNodes(t_sh *f)
{
	t_token *node;
	t_token *tmp;

	node = f->token;
	while (node != NULL)
	{
		tmp = node->next;
		if (!node)
			break ;
		if (!(node->token_str))
		{
			ddl_removeToken(&(f->token), node);
		}
		node = tmp;
	}
	if (f->token == NULL)
		return (1);
	return (0);
}


/* token a token , expande os $ na str, remove quotes e elimina tokens vazios */
int	_expander(t_sh *f)
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
		if (node->token_str)
			rmvQuotes(node);
		node = node->next;
	}
	if (rmvNodes(f))
		return (1);
	return (0);
}
