/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:33:22 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/07 18:33:24 by mbetcher         ###   ########.fr       */
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
