/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_or_not.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:35:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 23:17:04 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (node == NULL)
		return ;
	if (node->hd)
		free(node->hd);
	if (node->command)
		free(node->command);
	if (node->split && node->split[0])
	{
		while (node->split[i])
			free(node->split[i++]);
		free(node->split);
	}
}

void	ft_reset(t_minishell *data)
{
	t_node	*current;
	t_node	*tmp;

	if (data->line)
		free(data->line);
	if (!data->start_node)
		return ;
	current = data->start_node;
	while (current)
	{
		free_node(current);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	init_node(current);
}

void	free_all(t_minishell *data)
{
	t_node	*current;
	t_node	*tmp;
	t_env	*current_var;
	t_env	*tmp_var;

	if (data->line)
		free(data->line);
	if (!data->start_node)
		return ;
	if (data->start_node->next != NULL)
		free(data->pipe_tab);
	current = data->start_node;
	free_tab(data->export);
	free_tab(data->envp);
	while (current != NULL)
	{
		free_node(current);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	current_var = data->var;
	free_env_vars(data);
}
