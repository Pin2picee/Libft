#include "../minishell.h"
/* 
    Compte le nombre de variables dans t_env
*/
size_t	count_env_vars(t_env *env_list)
{
	size_t	count;
	t_env	*current;

	current = env_list;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
/*
    Alloue un tableau de pointeurs pour stocker les variables d'environnement
	leak :  a faire
*/

char	**allocate_env_tab(size_t count)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
	{
		perror("malloc");
		exit(1);
	}
	return (tab);
}
/*
    Remplit un tableau alloué avec des chaînes formatées
	Leak : a faire
*/

void	fill_env_tab(char **tab, t_env *env_list, size_t count)
{
	size_t	i;
	t_env	*current;

	i = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
			tab[i] = malloc(strlen(current->key)
					+ strlen(current->value) + 4);
		else
			tab[i] = malloc(strlen(current->key) + 1);
		if (!tab[i])
		{
			perror("malloc");
			exit(1);
		}
		if (current->value)
			sprintf(tab[i], "%s=\"%s\"", current->key, current->value);
		else
			sprintf(tab[i], "%s", current->key);
		i++;
		current = current->next;
	}
	tab[i] = NULL;
}
/*
    Convertie variables d'environnement (t_env) en deux tableaux de chaînes : envp et export.
	Leak : a faire
*/

void	convert_env_to_tab(t_minishell *data)
{
	size_t	count;

	count = count_env_vars(data->var);
    // char **envp
	data->envp = allocate_env_tab(count);
	fill_env_tab(data->envp, data->var, count);
    // char **export
	data->export = allocate_env_tab(count);
	fill_env_tab(data->export, data->var, count);
}
