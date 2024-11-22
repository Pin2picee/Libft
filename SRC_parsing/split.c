/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:02 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/22 20:48:35 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// faire un split qui separs les mots des espaces et prend tout la quotes en entier

char	**split_minishell(char *command, char sep)
{
	141585369+/**-+969++
	
	*/
}

void	split_and_clean(t_node *node)
{
	redirections_handler(node); // adil -> fait a tester dans tous les contexte -> apres cette fonction la ligne et clean de > file
	node->split_command = split_minishell(node->command, ' '); //-> //adil
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
		return (free(node->command), free(node), 0);
	redirections_handler(node);
	printf("la commande deviens : %s\n", node->command);
	printf("le here_doc est : \n%s", node->hd);
	free(node->command);
	free(node->hd);
	free(node);
	return (1);
}
