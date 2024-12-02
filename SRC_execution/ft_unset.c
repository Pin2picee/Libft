#include "../minishell.h"

void    unset_env_var(t_env **env_list, const char *name)
{
	t_env    *current;
	t_env    *previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (strcmp(current->key, name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

// fonction qui doit supprimer un env

void ft_unset(t_node *node)
{
	int	i;

	i = 1;
	if (node->split[1] == NULL)
		return;
	while (node->split[i])
	{
		unset_env_var(&(node->data->var), node->split[i]);
		i++;
	}
	return ;
	node->data->start_node = 0;
}
