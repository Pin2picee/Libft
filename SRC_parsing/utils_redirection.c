/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:51 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/20 20:31:33 by abelmoha         ###   ########.fr       */
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

void	ft_here_doc(char *final_word, t_node *node)
{
	char	*buf_line;
	char	*buf_hd;
	int		check;
	
	if (node->hd)
		free(node->hd);
	while (1)
	{
		buf_line = get_next_line(0);
		if (buf_line != NULL)
		{
			if (ft_strncmp(buf_line, final_word, ft_strlen(buf_line) + 1))// si end
				break;
			ft_strlcpy(buf_hd, )
			node->hd = malloc((ft_strlen(buf_line) + ft_strlen(node->hd)) * sizeof(char) + 1);
			check = ft_strlcat(buf_hd, buf_line, ft_strlen(node->hd) + ft_strlen(buf_line) + 1);
			if (check != ft_strlen(node->hd))
				return ;
		free(buf_line);
		}
	}
	if (buf_line)
		free(buf_line);
	// NE PAS OUBLIER DE LE FREE
}
// il faut supprimer le here_doc precedent dans le pipe seulement