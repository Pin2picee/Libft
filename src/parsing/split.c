/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:02 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/14 19:03:35 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_split(t_node *node)
{
	int	i;
	char	*command;
	char	**tab;
	
	i = 0;
	command = node->command;
	command = clean_command_redirection(command);
	node->command = malloc((char *) * ft_count_word(command));
	while ()

	//ajouter la fonction qui gere les redirections;
	if (is_quotes(tab))
	{
		
	}
	node->s_command = cleaning_redirections(tab);
	ft_free_tab(tab);
}


void	split_and_clean(t_node *node)
{
	node->command = redirections_handler(node->command); // adil -> faire 
	ft_split(node); //-> //adil
	quotes_var_handler(node);// -> mago ->enleve les quotes inutiles & attribue les valeurs des variables d'env
}

