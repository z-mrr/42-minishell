#include "../include/minishell.h"

void	lexer(t_frame *f)
{
	while (f->token->next != NULL)
	{
		tokenizeWord(f);
		printf("lex: %s\n", f->token->token_str);
		f->token = f->token->next;
	}
	tokenizeWord(f);
	while (f->token->prev != NULL) /*man de dll*/
		f->token = f->token->prev;
	//fill cmd struct
	printf("\nBEFORE PARSER\n");
	printList(f->token);
	parseCmds(f);
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
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
	lexer(f);
	//free_dll(f);
}
