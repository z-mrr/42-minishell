#include "../include/minishell.h"

void printList(t_token *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->token_str);
		head = head->next;
	}
}

char	ft_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			return (s[i]);
		else if (s[i] == '\'')
			return (s[i]);
		i++;
	}
	return (s[i]);
}

char	*ft_rmqte(char	*word, char qte)
{
	int	i;
	char	*s;
	int	sig;
	int	j;
	s = (char *)malloc(sizeof(char) * ft_strlen(word));
	i = 0;
	sig = 0;
	j = 0;
	while (word[i] != '\0')
	{
		if (!(sig) > 0 && word[i] == qte)
		{
			i++;
			sig = 1;
		}
		else
		{
			s[j] = word[i];
			i++;
			j++;
		}
	}
	s[i] = '\0';
	return (s);
}

char	*ft_addWords(char **s, int i, char qte)
{
	char	*word;
	char	*tmp;

	word = NULL;
	printf("rmqte== %s\n", word = ft_rmqte(s[i++], qte));
	while (s[i] != NULL && !(ft_strchr(word, qte)))
	{
		tmp = ft_strjoin(word, " ");
		free(word);
		word = ft_strjoin(tmp, s[i]);
		free(tmp);
		i++;
	}
	return (word); //por dar free
}

/* lê letra a letra, separando todas as palavras menos as dentro de " ou '  */
void	ft_lexer_split(t_frame *main_f, char *s)
{
	char	**split_s;
	int	i;
	char	qte;
	char	*word;

	//split por espaços
	split_s = ft_split(s, ' ');
	//create ll
	i = 0;
	while (split_s[i] != NULL)
	{
		printf("qte == %c\n", qte = ft_quotes(split_s[i]));
		if (qte != '\0')
		{
			word = ft_addWords(split_s, i, qte);
			i += ft_ll_append(&(main_f->token_f), word);
			//free(word);
		}
		else
			i += ft_ll_append(&(main_f->token_f), split_s[i]);
	}
	//free split_spaces
}
