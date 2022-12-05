#include "../include/minishell.h"

int	next_quote(char *s, int pos)
{
	int	sig;

	sig = 1;
	if (s[pos] == 34)
	{
		pos++;
		while (s[pos] != 34 && s[pos])
		{
			if (s[pos + 1] == 34)
				sig = 0;
			//if (s[pos] == '$') handle token
			pos++;
		}
	}
	else
	{
		pos++;
		while (s[pos] != 39 && s[pos])
		{
			if (s[pos + 1] == 39)
				sig = 0;
			pos++;
		}
	}
	if (sig)
		return (-1);
	while (s[pos] != ' ' && s[pos])
		pos++;
	return (pos);
}
