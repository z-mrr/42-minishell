#include "../include/minishell.h"

void	expandToken(t_token *token) //se '=' u '$' expande para os respetivos valores(exceptions aspas); remove aspas
{
	
}

void	parser(t_frame *f)
{
	t_token	*head;

	head = f->token;
	while (head != NULL)
	{
		if (head->token_type == 'N')
			expandToken(head);
		head = head->next;
	}
}

void	lexer(t_frame *f) //os operadores definem o resto dos tokens!!
{
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') //dentro de quotes 
			next_quote(f);
		else if (findOperator(f->str[f->pos])) //operador
			lexOp(f);
		else if (f->str[f->pos] == ' ') //final de word
			lexFwd(f);
		else //args
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
	parser(f);
	printList(f->token);
}
