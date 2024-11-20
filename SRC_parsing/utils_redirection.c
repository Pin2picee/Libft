/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:51 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/19 20:22:03 by abelmoha         ###   ########.fr       */
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
	while (!ft_strchr("><", str[(*i)]))
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