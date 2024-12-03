/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:19:08 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/27 21:45:15 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t    fill_tab_element(char **tab, t_env *current, size_t i)
{
    size_t    key_len;
    size_t    value_len;

    key_len = strlen(current->key);
    if (current->value)
        value_len = strlen(current->value);
    else
        value_len = 0;
    if (current->value)
        tab[i] = malloc(key_len + value_len + 4);
    else
        tab[i] = malloc(key_len + 1);
    if (!tab[i])
    {
        perror("malloc");
        exit(1);
    }
    ft_strlcpy(tab[i], current->key, key_len + 1);
    if (current->value)
    {
        ft_strlcat(tab[i], "=\"", key_len + 3);
        ft_strlcat(tab[i], current->value, key_len + value_len + 3);
        ft_strlcat(tab[i], "\"", key_len + value_len + 4);
    }
    return (i + 1);
}

void    fill_env_tab(char **tab, t_env *env_list, size_t count)
{
    size_t    i;
    t_env    *current;

    i = 0;
    current = env_list;
    while (current)
    {
        i = fill_tab_element(tab, current, i);
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
	data->export = allocate_env_tab(count);// char **export
	data->envp = allocate_env_tab(count);
	fill_env_tab(data->export, data->var, count);
	fill_env_tab(data->envp, data->var, count);
}
