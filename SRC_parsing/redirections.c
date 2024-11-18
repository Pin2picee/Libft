/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/18 13:09:49 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// fonction qui renvoie le name_file sans cote les doubles quotes qui entoure le name_file

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
	return (ft_strdup(copy));
}
// fonctions do_fd -> creer un file et qui creer les fd ou les ouvre et les mes dans les noeuds
void	do_fd(char *filename, int option, t_node *node)
{
	
	if (option == 1)
		node->fd_out = open(filename, O_CREAT, O_TRUNC); //TRUNC
	if (option == 2)
		node->fd_out = open(filename, O_CREAT, O_APPEND); // APPEND
	if (option == 3)
		node->fd_in = open(filename, O_RDONLY); // FD_IN
	if (node->fd_in < 0)
		perror("Error : File no exist\n");
	//if (option == 4)
		//here_doc
	free(filename);
}
// fonction
int	redirection(char *name_f, char c, t_node *node)
{
	int	i;
	int	j;
	char file[FILENAME_MAX];
	int	option;// 1 = trunc; 2 = append; 3 = redirection d'entre; 4 = here_doc 
	
	i = 0;
	j = 0;
	option = 1;// trunc
	if (c == '<' && ft_strchr("<", name_f[i]))
		option = 3;
	else if(name_f[i] == '>' && name_f[i] == c)// si >> append
		option = 2;
	else if (name_f[i] == '<' && name_f[i++] == c)// si << here doc
		option = 4;
	if (name_f[i] == '>' || name_f[i] == '<') // le cas ou >>> ou <<<
		return (-42);
	if (name_f[i - 1] != c && ft_strchr("><", name_f[i - 1]))// le cas ou >< ou ><
		return (-42);
	while (name_f[i] == ' ' || name_f[i] == '\t')//passe tant que espace si espace
		i++;
	if (ft_strchr("><", name_f[i]))// le cas ou >> >file ou l'inverse
		return (-42); // fonction printf
	while (name_f[i] != ' ' && name_f[i] != '\t' && name_f[i] && !ft_strchr("><", name_f[i]))
		file[j++] = name_f[i++]; // copie du file
	return (do_fd(clean_quotes(file), option, node), i); // creer le fichier avec append ou trunc et gere le here_doc
}

void	clean_commands(t_node *node)
{
	char	*str;
	int		i;
	int		j;
	str = ft_calloc(ft_strlen(node->command), sizeof(char));
	i = 0;
	j = 0;
	while (node->command[i])
	{
		if (node->command[i] == '"' || node->command[i] == '\'')
		{
			j+= ft_strlcpy(str + j, node->command + i, quote_chr(node->command, i) - i);// a verifier
			i = quote_chr(node->command, i);
			
		}
		if (ft_strchr("<>", node->command[i]))
		{
			ft_pass_redirection
		}
		str[j++] = node->command[i++];
	}
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
	clean_commands(node);
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

