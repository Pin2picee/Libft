/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:02 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/22 00:35:39 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	split_and_clean(t_node *node)
{
	redirections_handler(node); // adil -> fait a tester dans tous les contexte -> apres cette fonction la ligne et clean de > file
	ft_split(node->command, ' '); //-> //adil
	quotes_var_handler(node->split_command, node->data);// -> mago ->enleve les quotes inutiles & attribue les valeurs des variables d'env
}

int	main(int argc, char **argv)
{
	t_node *node;
	
	node = malloc (sizeof(t_node));
	node->command = ft_calloc(1000,  sizeof(char));
	ft_strlcpy(node->command, argv[1], (size_t)1000);
	printf("%s\n", node->command);
	node->fd_in = 0;
	node->fd_out = 1;
	node ->hd = NULL;
	if (redirections_syntax(argv[1]))
		return (0);
	redirections_handler(node);
	printf("la commande deviens : %s\n", node->command);
	printf("le here_doc est : \n%s", node->hd);
	free(node->command);
	free(node->hd);
	free(node);
	return (1);
}