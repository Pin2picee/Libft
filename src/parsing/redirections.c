/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/14 19:03:35 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(char *name_f, char c)
{
	int	i;
	bool append;
	bool hd;
	
	if(name_f[i] == '>' && name_f[i] == c)
		append = true;
	if (name_f[i] == '<' && name_f[i++] == c)
		hd = true;
	while (name_f[i])
	{
		if (name_f[i])
		i++;
	}	
}

char	*redirections_handler(char *command)
{
	int	i;
	
	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
			i = quote_chr(command, i) + 1;
		if (command[i] == '>')
		{
			i++;
			redirection(command + i, command[i]);
		}
		i++;
	}
}
Changement dans la gestion du hd. Zsh na pas la meme gestion que bash du hd.
pour chaque hd nous creerons des fichiers temporaires
faire attention a bien supprime chaque fichier temporaire apres l execution
on utilisera un flag pour savoir 