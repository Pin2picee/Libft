#include "../include/minishell.h"

void	free_env_vars(t_data *data)
{
	t_var	*current;
	t_var	*tmp;

	current = data->var_data;
	while (current)
	{
		tmp = current;
		free(tmp->key);
		free(tmp->value);
		current = current->next;
		free(tmp);
	}
	data->var_data = NULL;
}
