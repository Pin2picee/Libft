/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_or_not.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:35:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/27 21:15:35 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * a chaque boucle il faut free
 * les variable de ma data et mes noeuds
 * 
 */

void	free_node_env(t_env *current_var)
{
	if (current_var->key)
		free(current_var->key);
	if (current_var->value)
		free(current_var->value);
}
void	free_node(t_node *node)
{
	int	i;
	
	i = 0;
	if (node->hd)
		free(node->hd);
	if (node->command)
		free(node->command);
	if (node->split[0])
	{
		while(node->split[i])
			free(node->split[i++]);
		free(node->split);
	}
}
void	ft_reset(t_minishell *data)
{
	t_node *current;
	t_node *tmp;
	
	if (data->line)
		free(data->line);
	if (!data->start_node)
		return ;
	current = data->start_node;
	while (current)
	{
		free_node(current);// free le contenu du noeuds
		tmp = current->next;// mon temo pointe sur le prochaine
		free(current);// je free le noeud actuel
		current = tmp; // je point sur le prochain
	}
}

void	free_all(t_minishell *data)
{
	t_node *current;
	t_node *tmp;
	t_env	*current_var;
	t_env	*tmp_var;
	
	if (data->line)
		free(data->line);
	if (!data->start_node)
		return ;
	current = data->start_node;
	while (current)
	{
		free_node(current);// free le contenu du noeuds
		tmp = current->next;// mon temo pointe sur le prochaine
		free(current);// je free le noeud actuel
		current = tmp; // je point sur le prochain
	}
	current_var = data->var;
		while (current_var)
		{
			free_node_env(current_var);// free le contenu
			tmp_var = current_var->next;// un tmp sur le prochain
			free(current_var);//free le noeud
			current_var = tmp_var;// mon pointeur = au prochaine
		}
	free_env_vars(data);
}
