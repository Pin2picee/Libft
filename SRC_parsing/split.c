/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:02 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/16 19:18:19 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	split_and_clean(t_node *node)
{
	node->command = redirections_handler(node); // adil -> faire 
	ft_split(node); //-> //adil
	quotes_var_handler(node);// -> mago ->enleve les quotes inutiles & attribue les valeurs des variables d'env
}

