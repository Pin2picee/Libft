#include "../minishell.h"

int is_bn(char *str)
{
    int i;
    if(!str)
		return(0);
	i = 1;
	if(str[0] == '-')
	{
		while(str[i])
		{
			if(str[i] != 'n')
				return(0);
			i++;
		}
	}
    return (1);
}

int	ft_echo(t_node *node)
{
    int i;
    int flag_n;

    flag_n = is_bn(node->split[1]);
    if (flag_n == 1)
        i = 2;
    else
        i = 1;
    while(node->split[i])
    {
        ft_putstr_fd(node->split[i], node->fd_out);
        write(1, " ", 1);
        i++;
    }
    if(!flag_n)
        write(1, "\n", 1);
	return(0);
}