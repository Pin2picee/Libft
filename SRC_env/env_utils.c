/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:19:24 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/28 17:33:20 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	free_tab(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		free(export[i]);
		i++;
	}
	free(export);
}
