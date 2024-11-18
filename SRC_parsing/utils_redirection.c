/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:51 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/18 23:05:53 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cpy_file(char *file, char *name_f, int *i, int j)
{
	char	quote;
	
	if (ft_strchr("\"\'", name_f[(*i)]))
	{
		quote = name_f[(*i)];
		(*i)++;
		while (name_f[(*i)] != quote)
			file[j++] = name_f[(*i)++]; // copie du file
	}
	else
	{
		while (name_f[(*i)] != ' ' && name_f[(*i)] != '\t'
			&& name_f[(*i)] && !ft_strchr("><", name_f[(*i)]) && name_f[(*i)] != '|')
			file[j++] = name_f[(*i)++]; // copie du file
	}
}

void	ft_pass_redirection(char *str, int *i)
{
	char quote;
	
	while (ft_strchr("><", str[(*i)]))
		(*i)++;
	while (str[(*i)] == ' ')	
		(*i)++;
	while (str[(*i)])
	{
		if (ft_strchr("\"\'", str[(*i)]))
		{
			quote = str[(*i)];
			while (str[(*i)] != quote)
				(*i)++;
			(*i)++;
		}
		while (!ft_strchr(" \t", str[(*i)]))
			(*i)++;
	}
}
