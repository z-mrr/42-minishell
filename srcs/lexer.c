#include "../include/minishell.h"

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
