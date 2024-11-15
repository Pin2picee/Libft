/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/15 21:09:36 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// fonction qui renvoie le name_file sans cote et si ' est dans "" -> "fil'e1" alors on l'envoie comme ca "fil'e1"
char	*clean_quotes(char *file)
{
	char	copy[FILENAME_MAX];
	int		i;
	int		j;
	char	quotes;
	
	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == '"' || file[i] == '\'')
		{
			quotes = file[i];
			i++;
			while (file[i] != quotes && file[i])
			{
				copy[j] = file[i++];
				j++;
			}
			i++;
		}
		if (file[i])
			copy[j] = file[i++];
		j++;
	}
	return (copy);
}
// fonctions do_fd a faire

int	redirection(char *name_f, char c, t_node *node)
{
	int	i;
	int	j;
	char file[FILENAME_MAX];
	int	option;// 1 = trunc; 2 = append; 3 = redirection d'entre; 4 = here_doc 
	
	i = 0;
	j = 0;
	option = 1;// trunc
	if (c == '<' && !t_strchr("<>", name_f[i]))
		option = 3;
	else if(name_f[i] == '>' && name_f[i] == c)// si >> append
		option = 2;
	else if (name_f[i] == '<' && name_f[i++] == c)// si << here doc
		option = 4;
	if (name_f[i] == '>' || name_f[i] == '<') // le cas ou >>> ou <<<
		return (-42);
	if (name_f[i] != c && ft_strchr("><", name_f[i]))// le cas ou >< ou ><
		return (-42);
	while (name_f[i] == ' ' || name_f[i] == '\t')
		i++;
	if (ft_strchr("><", name_f[i]))// le cas ou >> >file ou l'inverse
		return (-42); // fonction printf
	while (name_f[i] != ' ' && name_f[i] != '\t' && name_f[i] && !ft_strchr("><", name_f[i]))
		file[j++] = name_f[i++]; // copie du file
	return (do_fd(clean_quotes(file), option, node), i); // creer le fichier avec append ou trunc et gere le here_doc
}

char	*redirections_handler(t_node *node)
{
	int	i;
	
	i = 0;
	while (node->command[i])
	{
		if (node->command[i] == '"' || node->command[i] == '\'')
			i = quote_chr(node->command, i) + 1;
		if (node->command[i] == '>' || node->command[i] == '<')
			i = redirection(node->command + i + 1, node->command[i], node); // j'envoie juste le > file et il me renvoie a l'espace
		if (i == -42)
		{
			printf("problem with redirection");
			return (NULL);
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