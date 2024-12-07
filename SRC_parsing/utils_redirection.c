/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:51 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 01:45:17 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cpy_file(char *file, char *name_f, int *i, int j)
{
	char	quote;
	
	while (name_f[*i] && ft_strchr(">< \t", name_f[*i]))
			(*i)++;
	ft_bzero(file, FILENAME_MAX);
	while (name_f[*i])
	{
		while (name_f[*i] && ft_strchr("\"\'", name_f[*i]))
		{
			quote = name_f[*i];
			file[j++] = name_f[(*i)++];
			while (name_f[*i] != quote && name_f[*i])
				file[j++] = name_f[(*i)++]; // copie du file dans les quotes
			if (ft_strchr("\"\'", name_f[*i]) && name_f[*i])
				file[j++] = name_f[(*i)++];
		}
		if (name_f[*i] && name_f[*i] != ' ' && !ft_strchr("<>", name_f[*i]))
		{
			while (name_f[*i] && name_f[*i] != ' ' && name_f[*i] != '\t'
				&& !ft_strchr("><", name_f[*i]) && name_f[*i] != '|')
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

int	ft_here_doc(char *final_word, t_node *node)
{
	char	*buf_line;
	char	*buf_hd;
	char	*buf_line_with_newline;

	buf_line = NULL;
	verif_here_doc(node);
	while (1)
	{
		if (!(buf_line = readline(">")) && control_d_herdoc(buf_line, final_word, node))
			break ;
		if (buf_line != NULL)
		{
			if (!ft_strncmp(buf_line, final_word, 1000))
				return (free(buf_line), ft_tkt(node), 0);
			buf_line_with_newline = ft_strjoin(buf_line, "\n");
			free(buf_line);
			buf_hd = ft_calloc(ft_strlen(node->hd) + 1, sizeof(char));
			if (!buf_hd)
				return (printf("error malloc"), 0);
			ft_strlcpy(buf_hd, node->hd, ft_strlen(node->hd) + 1);
			free(node->hd);
			node->hd = ft_strjoin(buf_hd, buf_line_with_newline);
			free(buf_line_with_newline);
			free(buf_hd);
		}
	}
}
