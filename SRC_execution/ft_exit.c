#include "../minishell.h"

int str_is_digit(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))// n'est pas un nombre
			return (0);
		i++;
	}
	return (1);
}

void    ft_exit_handler(t_node *node, int tmp_nb)
{
	ft_printf("exit\n");
	if (!(node->split[1]) && node->data->start_node->next == NULL)// si exit et pas exit dsds ou exit | dsds
	{
		free_all(node->data);
		exit(0);// si pas d'arg
	}
	else if (!str_is_digit(node->split[1]))// si le permier arg n'esst pas un nombre
	{
		printf("minishell: exit %s: numeric argument is required", node->split[1]);
		free_all(node->data);
		exit(2);      
	}
	else if (node->split[2])// si plus de 1 arguments -> alors to many arguments
	{
		printf("minishell: exit: too many arguments");
		tmp_nb = ft_atoi(node->split[1]);
		free_all(node->data);
		exit(tmp_nb);
	}
	tmp_nb = ft_atoi(node->split[1]);
	free_all(node->data);
	exit(tmp_nb);
}

void    ft_exit(t_node *node)
{
	if (node->data->start_node->next != NULL)// si pipe alors rien faire juste exit le processus enfant
		exit(0);
	else
		ft_exit_handler(node, 0);

}

