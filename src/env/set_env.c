#include "../include/minishell.h"

t_var	*create_var(const char *key, const char *value)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
	{
		printf("Erreur : malloc a échoué\n");
		exit (1);
	}
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->next = NULL;
	return (new_var);
}

t_var	*get_env_var(t_var *var_data, const char *key)
{
	t_var	*current;

	current = var_data;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	init_env(t_data *data, char **envp)
{
	t_var	*current;
	t_var	*new_var;
	int		i;
	char	*equal_sign;

	i = 0;
	current = NULL;
	data->var_data = NULL;
	while (envp[i])
	{
		equal_sign = strchr(envp[i], '=');
		if (equal_sign)
		{
			new_var = create_var(strndup(envp[i],
						equal_sign - envp[i]), equal_sign + 1);
			if (!data->var_data)
				data->var_data = new_var;
			else
				current->next = new_var;
			current = new_var;
		}
		i++;
	}
	data->envp = NULL;
}
