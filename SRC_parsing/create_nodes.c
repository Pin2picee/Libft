/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:14:14 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/18 15:43:48 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*find_last_node(t_minishell *data)
{

}

void	create_nodes(t_minishell *data)
{
	char	*tab;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	tab = data->line;

	while (tab[i])
	{
		if (tab[i] == '\'')
		{
			i++;
			while (tab[i] != '\'')
				i++;
		}
		if (tab[i] == '\"')
		{
			i++;
			while (tab[i] != '\"')
				i++;
		}
		if (tab[i] == '|')
		{
			append_nodes(data, last, i);
			last = i + 1;
		}
		i++;
	}
	append_nodes(data, last, i);
}

void	append_nodes(t_minishell *data, int start, int end)
{
	t_node	*new_node;
	t_node	*last_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return ;
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->next = NULL;
	if (data->start_node == NULL)
		data->start_node = new_node;
	else
	{
		last_node = find_last_node(data);
		last_node->next = new_node;
	}
	add_line_to_node(new_node, start, end);
}

void	add_line_to_node(t_node *node, int start, int end)
{
	int		i;

	i = 0;
    node->command = malloc((end - start) + 1);
	if (node->command == NULL)
		return ;
    while (start < end)
    {
		   node->command[i] = node->command[start];
		   i++;
		   start++;
    }
	node->command[i] = '\0';
	return ;
}
