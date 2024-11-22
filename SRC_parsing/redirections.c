/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/22 00:40:14 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fonctions do_fd -> creer un file et qui creer les fd ou les ouvre et les mes dans les noeuds
void	do_fd(char *filename, int option, t_node *node)
{
	int	len;
	char	*Error;

	len = 0;
	tab_len(filename, &len, node->data);
	if (len != 0)
		filename = ft_clean_tab(filename, len, node->data);// clean les ""
	if (option == 1)
		node->fd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666); //TRUNC
	if (option == 2)
		node->fd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666); // APPEND
	if (option == 3)
		node->fd_in = open(filename, O_RDONLY); // FD_IN
	if (option == 3 && node->fd_in < 0)
	{
		Error = ft_strjoin("Minishell: ", filename);
		perror(Error);
		free(Error);
		exit(1);
	}
	if (option == 4)
		ft_here_doc(filename, node);//TODO -> 
	free(filename);
}

// fonction qui recupere le filname et appel une fonction qui va creer un fichier au filname
int	go_redirection(char *name_f, char c, t_node *node, int i)
{
	char file[FILENAME_MAX];
	int	option;// 1 = trunc; 2 = append; 3 = redirection d'entre; 4 = here_doc 
	int	j;

	init_j_and_option(&j, &option);//gagner des ligne -> oui gros rat
	if (c == '<' && !ft_strchr("<>", name_f[i]))// si redire entre
		option = 3;
	if(name_f[i] == '>' && name_f[i] == c)// si >> append
		option = 2;
	if (name_f[i] == '<' && name_f[i] == c)// si << here doc
		option = 4;
	if ((name_f[i + 1] == '>' || name_f[i + 1] == '<') && ft_strchr("><", name_f[i]))// le cas ou >>> ou <<<
		return (ft_printf("test1\n"), -42);
	if ((name_f[i] != c && ft_strchr("><", name_f[i])))// le cas ou >< ou ><
		return (ft_printf("test2\n"), -42);
	if (name_f[i] == ' ' || name_f[i] == '\t')
	{
		while (name_f[i] == ' ' || name_f[i] == '\t')//passe tant que espace si espace
			i++;
		if (ft_strchr("><", name_f[i]))// le cas ou >> >file ou l'inverse
			return (ft_printf("fuck\n"), -42); // fonction printf
	}
	if (ft_strchr("\'\"", name_f[i + 1]) && name_f[i])
		i++;//si append
	return (ft_cpy_file(file, name_f, &i, j), do_fd(ft_strdup(file), option, node), i + 1); // creer le fichier avec append ou trunc et gere le here_doc
}
//la fonction clean_command renvoie la chaine sans > file
void	clean_commands(t_node *node)
{
	char	*str;
	int		i;
	int		j;
	str = ft_calloc((int)ft_strlen(node->command) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (node->command[i])
	{
		while (node->command[i] && ft_strchr("<>", node->command[i]))
			ft_pass_redirection(node->command, &i);// une fonction qui passe le file et les redirections
		if (node->command[i] == '"' || node->command[i] == '\'')
		{
			j+= ft_strlcpy(str + j, node->command + i, quote_chr(node->command, i) - i + 2);// a verifier
			i = quote_chr(node->command, i);
			
		}
		else
			str[j++] = node->command[i++];
	}
	//if (i == (ft_strlen(node->command) - 1)
	free(node->command);
	node->command = str;
}
// fonction principal
void	redirections_handler(t_node *node)
{
	int	i;
	int	check;
	
	i = 0;
	while (node->command[i])
	{
		if (node->command[i] == '"' || node->command[i] == '\'')
			i = quote_chr(node->command, i) + 1;
		while ((node->command[i] == '>' || node->command[i] == '<') && node->command[i])
		{
			check = go_redirection(node->command + i + 1, node->command[i], node, 0);
			if (i == (check += (-42)))// a voir car marche pas
			{
				//fonction qui free tout
				return ; // j'envoie juste le "> file" et il me renvoie apres le name_file
			}	
			i += check;
		}
		i++;
	}
	if (node->command)
		clean_commands(node);
	return ;
}
/*
	-redirections_handler -> parcours ma chaine et fait envoie
	 			les redirections dans redirections et les here_doc qu'il y a 
	-redirections parcours ce qu'il y a apres un chevront 
				et appel do_fd qui creer le fichier en fonction de la redirection precedente
*/

