#include "../minishell.h"

void	ft_pwd(t_minishell *data)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	printf("%s\n", buffer);
	free(buffer);
	data->exit_code = 0;
}
