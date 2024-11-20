/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:14:14 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/20 17:28:43 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *find_last_nodes(t_node *node)
{
    if (!node)
        return NULL; 
    while (node->next)
    {
        node = node->next;
    }
    return node;
}

void	add_line_to_node(t_node *node, int start, int end, char *line)
{
	int	i;

	i = 0;
	node->command = malloc((end - start) + 1);
	if (node->command == NULL)
		return ;
	while (start < end)
	{
		node->command[i] = line[start];
		i++;
		start++;
	}
	node->command[i] = '\0';
}

void	append_nodes(t_minishell *data, int start, int end, char *tab)
{
	t_node	*new_node;
	t_node	*last_nodes;

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
		last_nodes = find_last_nodes(data->start_node);
		last_nodes->next = new_node;
	}
	add_line_to_node(new_node, start, end, tab);
}

void	create_nodes(t_minishell *data)
{
	char	*tab;
	int	i;
	int	last;
	char	quote;
	
	last = 0;
	i = 0;
	tab = data->line;
	//data->start_nodes == NULL;
	while (tab[i])
	{
		if (tab[i] == '\'' || tab[i] == '"')
		{
			quote = tab[i];
			i++;
			while (tab[i] != quote)
				i++;
		}
		if (tab[i] == '|')
		{
			append_nodes(data, last, i, tab);
			last = i + 1;
		}
		i++;
	}
	append_nodes(data, last, i, tab);
}






