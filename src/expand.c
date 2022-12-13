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
char	*_getExpansion(char *old_str, int pos)
{
	char	*expansion;

	expansion = NULL;
	printf("pos: %i, str: %s\n", pos, old_str);

	printf("var: %s\n", expansion = ft_substr(old_str, pos,  _endVarPos(old_str, pos + 1) - pos)); /* devolve respectiva expansao; */

	/*get env*/
	free(expansion);

	return (NULL);
}

char	*_getRest(char *old_str, int pos)
{
	int	start;
	char	*left;

	left = NULL;
	start = pos;
	while (old_str[pos] != '$' && old_str[pos] != '\0')
		pos++;
	left = ft_substr(old_str, start, pos);
	return (left);
}

/* recebe uma str,  expande todos os $ */
char	*_expandStr(char *old_str, int pos)
{
	char	*expan;
	char	*new_str;
	char	*left;

	new_str = NULL;
	expan = NULL;
	while (old_str[pos])
	{
		printf("a esquerda: %s\n", left = _getRest(old_str, pos));
		printf("o expand: %s\n\n", expan = _getExpansion(old_str, pos));
		printf("pos: %i\n\n", pos = _endVarPos(old_str, pos + 1)); /* nova pos no final do que foi lido */
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
			node->token_str = _expandStr(tmp, 0);
			free(tmp);
		}
		if (!(node->token_str))
			{printf("node: %s", node->token_str);exit(-1);}
		//	rmvQuotes(node);
		node = node->next;
	}
}
