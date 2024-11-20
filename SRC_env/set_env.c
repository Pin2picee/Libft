#include "../minishell.h"

t_env	*create_var(const char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
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

t_env	*get_env_var(t_env *var_data, const char *key)
{
	t_env	*current;

	current = var_data;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	init_env(t_minishell *data, char **envp)
{
	t_env	*current;
	t_env	*new_var;
	int		i;
	char	*equal_sign;

	i = 0;
	current = NULL;
	data->var = NULL;
	while (envp[i])
	{
		equal_sign = strchr(envp[i], '=');
		if (equal_sign)
		{
			new_var = create_var(strndup(envp[i], equal_sign - envp[i]), equal_sign + 1);
			if (!data->var)
				data->var = new_var;
			else
				current->next = new_var;
			current = new_var;
		}
		i++;
	}
	data->envp = NULL;
}

// inclure le signe egale dans la key.

