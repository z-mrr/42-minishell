#include "../include/minishell.h"

/*  */
int	expandSingle(t_frame *f) //falta adicionar excepcoes $? $$
{
	char	*left; //o que ja foi lido
	char	*expansion; // o que vai tentar ser expandido
	char	*right; //o que falta ler
	char	*tmp;
	char	*new_line;

	new_line = NULL;
	left = NULL;
	expansion = NULL;
	right = NULL;
	tmp = NULL;

	if (f->pos >= 1)
		left = ft_substr(f->token->token_str, 0, f->pos); // ise existir le tudo para tras
	f->wd_begin = f->pos;
	f->pos++;
	while (f->token->token_str[f->pos] != '$' && f->token->token_str[f->pos] != ' ' && f->token->token_str[f->pos] != 34 && f->token->token_str[f->pos] != 39 && f->token->token_str[f->pos])
		f->pos++;
	expansion = NULL; /* expansion = get_env ft_substr(f->token->token_str, f->wd_begin, f->pos - f->wd_begin); */
	if (f->token->token_str[f->pos] != '\0')
		right = ft_substr(f->token->token_str, f->pos, ft_strlen(f->token->token_str) - f->pos);

	printf("\nleft= %s\n", left);
	printf("\nexpan= %s\n", expansion);
	printf("\nright= %s\n", right);

	tmp = ft_strjoin(left, expansion);
	if (left)
		free(left);
	if (expansion);
		free(expansion);

	printf("\ntmp= %s\n", tmp);

	new_line = ft_strjoin(tmp, right);

	if (right)
		free(right);

	printf("\nnew_line= %s\n", new_line);
	
	free(f->token->token_str);
	if (new_line)
	{
		f->token->token_str = ft_strdup(new_line);
		free(new_line);
	}
	else
		return (1);
	if (tmp)
		{f->pos = ft_strlen(tmp) - 1; free(tmp);}
	else
		f->pos = 0;
	return (0);
}

/* tenta expandir $ , caso str fique vazia apaga node */
int	expandStr(t_frame *f)
{
	printf("\nnew_str= %s\n", f->token->token_str);
	f->pos = 0;
	while (f->token->token_str[f->pos] != '\0') //expande todas as instancias de $var
	{
		if (f->token->token_str[f->pos] == 39) //dentro de ' vai ate prox '
		{
			f->pos++;
			while (f->token->token_str[f->pos] != 39)
				f->pos++;
			f->pos++;
		}
		else if (f->token->token_str[f->pos] == '$')
		{
			if (expandSingle(f)) //muda apenas 1 palavra
			{
				remove_dll(f);
				return (0);
			}
		}
		else
			f->pos++;
		printf("fpos%i fchar: %c\n", f->pos, f->token->token_str[f->pos]);
	}
	rmvQuotes(f); //arranjar "" (da return de ' ')
	return (1);
}

/* token a token expande $, caso token_str fique vazio, apaga token */
void	lexer(t_frame *f)
{
	while (f->token->next != NULL)
	{
		if (expandStr(f))
			f->token = f->token->next;
	}
	expandStr(f);
	if (f->token == NULL)
		{printf("\nNada para lexar- error handling\n"); exit(-1);}
	while (f->token->prev != NULL) /*man de dll*/
		f->token = f->token->prev;
}
