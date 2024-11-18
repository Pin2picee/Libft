#include "../minishell.h"

void	free_env_vars(t_minishell *data)
{
	t_env	*current;
	t_env	*tmp;

	current = data->var;
	while (current)
	{
		tmp = current;
		free(tmp->key);
		free(tmp->value);
		current = current->next;
		free(tmp);
	}
	data->var = NULL;
}
