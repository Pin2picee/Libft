/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:20:44 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/07 19:20:59 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_minishell *data)
{
	t_env	*current;

	current = data->var;
	while (current)
	{
		if (current->is_export_only == 0 && current->value)
			printf("%s=%s\n", current->key, current->value);
		else if (current->is_export_only == 0 && !current->value)
			printf("%s=\n", current->key);
		current = current->next;
	}
	data->exit_code = 0;
}
