#include "../minishell.h"
/*
    Analyse une chaîne de la forme nom=valeur pour en extraire séparément le nom et la valeur.
	Leak : a faire
*/
int	parse_name_value(char *arg, char **name, char **value)
{
	char	*equal_sign;
	int		name_length;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	name_length = equal_sign - arg;
	if (name_length == 0)
		return (0);
	*name = ft_strldup(arg, name_length);
	*value = ft_strdup(equal_sign + 1);
	if (!*name || !*value)
	{
		perror("malloc");
		exit(1);
	}
	return (1);
}
/*
    Met à jour une variable existante dans la liste chaînée t_env avec une nouvelle valeur.
*/

int	update_env_var(t_env *env_list, const char *name, const char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (strcmp(current->key, name) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
				current->is_export_only = 0;
			}
			else
				current->is_export_only = 1;
			return (1);
		}
		current = current->next;
	}
	return (0);
}
/*
    Ajoute une nouvelle variable dans la liste chaînée t_env.
*/

void	add_env_var(t_env **env_list, const char *name, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		perror("malloc");
		exit(1);
	}
	new_var->key = ft_strdup(name);
	if (value)
	{
		new_var->value = ft_strdup(value);
		new_var->is_export_only = 0;
	}
	else
	{
		new_var->value = NULL;
		new_var->is_export_only = 1;
	}
	new_var->next = *env_list;
	*env_list = new_var;
}
/*
    Met à jour une variable existante dans t_env, ou en ajoute une nouvelle si elle n'existe pas
*/

void	update_or_add(t_env **env_list, const char *name, const char *value)
{
	if (!update_env_var(*env_list, name, value))
		add_env_var(env_list, name, value);
}
