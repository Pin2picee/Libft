/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:31:03 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/23 22:36:42 by Pin2picee        ###   ########.fr       */
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
	
	if (pre_parsing(data->line)) // verif retour readline->main
		return (1);
	node = data->start_node;
	create_nodes(data); 
	while (node) //-> for every pipe : ligne clean et split clean
	{
		split_and_clean(node);// clean redirections for command AND split AND clean quotes split
		node = node->next;
	}
	return (0);
}
