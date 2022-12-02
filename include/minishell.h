#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define PURPLE "\x1B[35m"
# define RESET "\x1b[0m"

/* 
typedef struct s_command {
	
} t_command;
 */

//utils
char	*ft_strjoin(char const *s1, char const *s2);
