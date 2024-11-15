/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/15 13:03:10 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(char *name_f, char c)
{
	int	i;
	bool append;
	bool hd;
	char file[FILENAME_MAX];
	
	i = 0;
	j = 0;
	if(name_f[i] == '>' && name_f[i] == c)// si >> append
		append = true;
	else if (name_f[i] == '<' && name_f[i++] == c)// si << here doc
		hd = true;
	if (name_f[i] == '>' || name_f[i] == '<') // le cas ou >>> ou <<<
		return (-42);
	while (name_f[i] == ' ' || name_f[i] == '\t')
		i++;
	if ()
	while (name_f[i] != ' ' && name_f[i] != '\t' && name_f[i] && //redirections)
		file[j++] = name_f[i++];
	do_fd(file, append, hd); // creer le fichier avec append ou trunc et gere le here_doc
}

char	*redirections_handler(char *command)
{
	int	i;
	
	i = 0;
	while (command[i])
	{
		if (command[i] == '"' || command[i] == '\'')
			i = quote_chr(command, i) + 1;
		if (command[i] == '>' || command[i] == '<' )
			i = redirection(command + i + 1, command[i]); // j'envoie juste le > file et il me renvoie a l'espace
		if (i == -42)
			return (NULL);
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