/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:51 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/26 13:15:41 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cpy_file(char *file, char *name_f, int *i, int j)
{
	char	quote;
	
	while (name_f[*i] == ' ' || name_f[*i] == '\t' || ft_strchr("><", name_f[*i]))
			(*i)++;
	ft_bzero(file, FILENAME_MAX);
	while (name_f[*i])
	{
		while (ft_strchr("\"\'", name_f[*i]) && name_f[*i])
		{
			quote = name_f[*i];
			file[j++] = name_f[(*i)++];
			while (name_f[*i] != quote && name_f[*i])
				file[j++] = name_f[(*i)++]; // copie du file dans les quotes
			if (ft_strchr("\"\'", name_f[*i]) && name_f[*i])
				file[j++] = name_f[(*i)++];
		}
		if (name_f[*i] != ' ' && name_f[*i] && !ft_strchr("<>", name_f[*i]))
		{
			while (name_f[*i] != ' ' && name_f[*i] != '\t'
				&& name_f[*i] && !ft_strchr("><", name_f[*i]) && name_f[*i] != '|')
				file[j++] = name_f[(*i)++]; // copie du file
		}
		else
			break ;
	}
}

void	ft_pass_redirection(char *str, int *i)
{
	char quote;
	
	while (ft_strchr("><", str[(*i)]))
		(*i)++;
	while (str[(*i)] == ' ')	
		(*i)++;
	if (ft_strchr("\"\'", str[(*i)]))
	{
		while (ft_strchr("\"\'", str[(*i)]))
		{
			quote = str[(*i)++];
			while (str[(*i)] != quote && str[(*i)])
				(*i)++;
			(*i)++;
	
		}
	}
	while (!ft_strchr(">< ", str[(*i)]))
		(*i)++;
	if (ft_strchr("><", str[(*i)]))
		return ;
	while (ft_strchr(" \t", str[(*i)]) && str[(*i)])
		(*i)++;

}

void	init_j_and_option(int *i, int *option)
{
	(*i) = 0;
	(*option) = 1;//trunc
}

void	verif_here_doc(t_node *node)
{
	if (node->hd)
		free(node->hd);
	node->hd = NULL;
}

void	ft_here_doc(char *final_word, t_node *node)
{
	char	*buf_line;
	char	*buf_hd;
	
	verif_here_doc(node);
	while (1)
	{
		ft_printf("> ");
		buf_line = get_next_line(0);
		if (buf_line != NULL)
		{
			if (ft_strlen(buf_line) - 1 == ft_strlen(final_word) && !ft_strncmp(buf_line, final_word, ft_strlen(buf_line) - 1))// si end
				break ;
			buf_hd = ft_calloc(ft_strlen(node->hd) + 1, sizeof(char));
			if (buf_hd == NULL)
				return ;
			ft_strlcpy(buf_hd, node->hd, ft_strlen(node->hd) + 1);// on copie node->hd dans mon buf
			free(node->hd);
			node->hd = ft_strjoin(buf_hd, buf_line);// on join l'ancien ligne avec la nouvelle;
			free(buf_line);
			free(buf_hd);
		}
	}
	get_next_line(-42);
	free(buf_line);// On sort de la boucle seulement si mot de fin et si mot de fin alors il faut free(ma line)->get_next_line
}
// il faut supprimer le here_doc precedent dans le pipe seulement