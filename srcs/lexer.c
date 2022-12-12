#include "../include/minishell.h"

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

/* lê a var */
char	*getVar(t_token *node, int pos)
{
	int	start;
	char	*s;

	s = node->token_str;
	start = pos;
	pos++;
	//exceptions $? , $$
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == '?' || s[pos] == 34 || s[pos] == 39 || s[pos] == ' ')
		{
			if (pos - 1 == start && s[pos] == '?')
				return (ft_substr(s, start, pos + 1 - start));
			if (pos - 1 == start && s[pos] == '$')
				return (ft_substr(s, start, pos + 1 - start));
			return (ft_substr(s, start, pos - start));
		}
		pos++;
	}
	return (ft_substr(s, start , pos - start));
}

/* expande a var; null se nada */
char	*expandVar(char	*var)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strcmp(var, "$?"))
	{
		tmp = ft_strdup(var); //adicionar ultimo pid
		return (tmp);
	}
	if (ft_strcmp(var, "$$"))
	{
		tmp = ft_strdup(var); //adicionar current pid (n necessario secalhar)
		return (tmp);
	}
	if (ft_strcmp(var, "$"))
	{
		tmp = ft_strdup(var); //bc
		return (tmp);
	}
	if (1)
		return (NULL);
		/*get env*/
}


/* remove var da palavra */
void	removeVar(char **old_str, char *var, int pos)
{
	char	*new_str;
	char	*left;
	char	*right;

	new_str = NULL;
	left = NULL;
	right = NULL;
	if (pos)
		left = ft_substr(*old_str, 0, pos);
	if (pos + ft_strlen(var) != '\0')
		right = ft_substr(*old_str, pos + ft_strlen(var), ft_strlen(*old_str) - pos);
	if (left && right)
	{
		new_str = ft_strjoin(left, right);
		free(left);
		free(right);
	}
	else
	{
		if (left)
		{
			new_str = ft_strdup(left);
			free(left);
		}
		else if (right)
		{
			new_str = ft_strdup(right);
			free(right);
		}
	}
	free(*old_str);
	if (new_str == NULL)
		*old_str = NULL;
	else
		*old_str = new_str;
}

/* insere value na palavra */
void insertValue(char **old_str, char *value, int pos)
{
	char	*new_str;

	new_str = NULL;
	if (value == NULL)
		return ;
	if (!(*old_str[0]))
		*old_str = ft_strdup(value);
	else
		
	/*if ()*/
	/*	
		
	free(old_str);
	return (new_str);*/
}

/* expande 1 instancia de $ */
int	expandSingle(t_frame *f, t_token *node)
{
	char	*var;
	char	*tmp;
	char	*value;

	var = NULL;
	tmp = NULL;
	value = NULL;

	var = getVar(node, f->pos); /* get var*/ //por dar free
	printf("\n\n\n\n\nvar :%s\n\n", var);

	value = expandVar(var); /* expand var para value */ //por dar free
	printf("\n\n\n\n\nvalue1 :%s\n\n", value);

	printf("\n\nold s: %s\n", node->token_str);
	removeVar(&(node->token_str), var, f->pos); /* remove var from word */
	printf("\n\nnew s2: %s\n", node->token_str);

	insertValue(&(node->token_str), value, f->pos); //insere value na palavra (ou palavra toda);
	printf("\n\nnew s3: %s\n", node->token_str);

	f->pos = f->pos + ft_strlen(value);
	printf("\nf->pos: %i\n", f->pos);
	//exit(-1);
	if (!(node->token_str))
		return (1); //  se vazia apagar node
	return (0);
}


/* tenta expandir $ , caso str fique vazia apaga node */
int	expandStr(t_frame *f, t_token *node)
{
	f->pos = 0;
	while (node->token_str[f->pos] != '\0') //expande todas as instancias de $var
	{
		if (node->token_str[f->pos] == 39) //dentro de ' vai ate prox '
		{
			f->pos++;
			while (node->token_str[f->pos] != 39)
				f->pos++;
			f->pos++;
		}
		else if (node->token_str[f->pos] == '$')
		{
			if (expandSingle(f, node)) //expande cada '$' ; return null em caso de limpar a str
				return (1);
		//exit(-1);
		}
		else
			f->pos++;
		printf("fpos%i fchar: %c\n", f->pos, node->token_str[f->pos]);
	}
	rmvQuotes(f);
	return (0);
}

/* token a token expande $, caso token_str fique vazio, apaga token */
void	lexer(t_frame *f)
{
	t_token *node;
	t_token *tmp;

	node = NULL;
	node = f->token;
	tmp = NULL;
	while (node != NULL)
	{
		if (expandStr(f, node))
		{
			//exit(-1);
			tmp = node->next;
			ddl_removeToken(&(f->token), node);
			node = tmp;
		}
		else
			node = node->next;
	}
	if (f->token == NULL)
		{printf("\nNada para lexar- error handling\n"); exit(-1);}
	while (f->token->prev != NULL) /*man de dll*/
		f->token = f->token->prev;
}
