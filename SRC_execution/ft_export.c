/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:18:54 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/28 18:21:33 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// la fonction export dois modifier une variable ou si rien doit affichier TOUTES LA VARIABLES D'ENVIRONNEMENTS
void	ft_printf_export(t_minishell *data)
{
	int	i;

	i = 0;
	// faut le trier dabord
	//free_tab(data->export);
	convert_env_to_tab(data);
	bubble_sort(data->export);
	while (data->export[i])
	{
		printf("declare -x %s\n", data->export[i]);
		i++;
	}
}

// FONCTION qui sera appele dans l'execution
void	ft_export(t_node *node)
{
	int		i;
	int		j;
	char	*name;
	char	*value;

	i = 1;
	if (node->split[1] == NULL)
	{
		ft_printf_export(node->data);
		return ;
	}
	while (node->split[i])
	{
		j = 0;
		if (!ft_strchr(node->split[i], '='))
			update_or_add(&(node->data->var), node->split[i], NULL);
		else
		{
				parse_name_value(node->split[i], &name, &value);// attribut la name et la valeur a mes variables
				update_or_add(&(node->data->var), name, value);//ajoute ou met a jour ma variable d'environement
				free(name);
				free(value);
		}
		i++;
	}
}
