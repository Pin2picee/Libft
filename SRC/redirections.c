/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/14 15:20:57 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirectiom(char *name_f, char c)
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
/**
 * plan pour gerer les redirections:
{
	ce que je recois:
	{
		une ligne non parse 
	}
	ce que je dois retourner:
	{
		une ligne nettoyer de ses redirections:
	}
	les cas que je dois gerer:
	{
		s il y a plus de 2 > ou <;
		si il y a des redirections et rien apres;
		si cest un hd <<, ne pas le gerer
		{
			pa
		}
	}
}
*/