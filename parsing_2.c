/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:31:03 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/13 18:08:07 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (cleaning_redirections(data))
		return (1);
	create_nodes(data);
	
	while (node)
	{	
		split_and_clean(node);
		
		node = node->next;
	}
}
