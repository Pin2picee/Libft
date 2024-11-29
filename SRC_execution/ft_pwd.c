#include "../minishell.h"

void	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	printf("%s\n", buffer);
	free(buffer);
}