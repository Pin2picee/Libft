/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:18:54 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 19:30:43 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_printf_export(t_minishell *data)
{
	int	i;

	i = 0;
	convert_env_to_tab(data);
	bubble_sort(data->export);
	while (data->export[i])
	{
		printf("declare -x %s\n", data->export[i]);
		i++;
	}
}

int	ft_export(t_node *node, int i, int test)
{
	char	*name;
	char	*value;

	if (node->split[1] == NULL)
		return (ft_printf_export(node->data), 1);
	while (node->split[i])
	{
		if (!ft_strchr(node->split[i], '=') && !ft_isdigit(node->split[i][0]))
			update_or_add(&(node->data->var), node->split[i], NULL);
		else
		{
			test = parse_name_value(node->split[i], &name, &value);
			if (test && (!ft_isdigit(name[0])))
				update_or_add(&(node->data->var), name, value);
			else
				ft_putstr_fd("export: not a valid identifier\n", 2);
			if (test)
				free(value);
			if (test)
				free(name);
		}
		i++;
	}
	node->data->exit_code = 0;
}
