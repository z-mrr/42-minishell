#include "../include/minishell.h"

int	checkqts(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

// '=' //palavra a esquerda n pode ter aspas; palavra a direita pode; nao pode estar dentro de aspas; se invalido corta bocado
void	twEqual(t_frame *f, t_token *head)
{
	char	*pesq;
	char	*pdir;

	pesq = ft_substr(head->token_str, f->wd_begin, f->pos - f->wd_begin);
	if (checkqts(pesq))
	{
		free(pesq);
		return ;
	}
	printf("boa"); exit(-1);
	f->pos++;
}

/* lida com '$' e '=' */
void	tokenizeWord(t_frame *f, t_token *head)
{
	f->pos = 0;
	while (head->token_str[f->pos])
	{
		f->wd_begin = f->pos;
		// '=' //palavra a esquerda n pode ter aspas; palavra a direita pode; nao pode estar dentro de aspas; se invalido corta bocado
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
void	lexer(t_frame *f)
{
	t_token *head;

	head = f->token;
	while (head != NULL)
	{
		if (head->token_type != 'O')
			tokenizeWord(f, head);
		head = head->next;
	}
	//fill cmd struct
}

/* tokenizer; separa dentro de aspas, operadores e palavras */
void	tokenizer(t_frame *f) //os operadores definem o resto dos tokens!!
{
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') //dentro de quotes 
			lexQuote(f);
		else if (findOperator(f->str[f->pos])) //operador
			lexOp(f);
		else if (f->str[f->pos] == ' ') //final de word
			lexWdend(f);
		else //args
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
	lexer(f);
	printList(f->token);
}
