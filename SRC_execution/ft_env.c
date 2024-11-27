#include "../minishell.h"


// pour la commande env affiche chaque noeud de la liste sous cette forme key=value
void	ft_env(t_minishell *data)
{
	t_env	*current;

	current = data->var;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
