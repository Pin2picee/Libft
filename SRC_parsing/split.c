/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:02 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/19 18:36:40 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	split_and_clean(t_node *node)
{
	redirections_handler(node); // adil -> faire 
	ft_split(node->command, ' '); //-> //adil
	quotes_var_handler(node->split_command, node->data);// -> mago ->enleve les quotes inutiles & attribue les valeurs des variables d'env
}

int	main(int argc, char **argv)
{
	t_node *node;
	
	node = malloc (sizeof(t_node));
	node->command = ft_calloc(1000,  sizeof(char));
	ft_strlcpy(node->command, argv[1], 1000);
	printf("%s\n", node->command);
	node->fd_in = 0;
	node->fd_out = 1;
	redirections_handler(node);
	printf("la commande deviens : %s\n", node->command);
	free(node->command);
	free(node);
	return (1);
}