/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:31:03 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 19:01:53 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipes_chr(char	*readline, int i)
{
	int	j;

	j = i + 1;
	while (readline[j] && readline[j] != readline[i])
		j++;
	if (readline[i] == readline[j] && readline[j] == '|')
		return (i);
	else
		return (-42);
}

int	parsing(t_minishell *data)
{
	t_node	*node;

	data->start_node = NULL;
	if (pre_parsing(data->line))
		return (1);
	create_nodes(data, 0);
	node = data->start_node;
	while (node)
	{
		split_and_clean(node);
		node = node->next;
	}
	return (0);
}
