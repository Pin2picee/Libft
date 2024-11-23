/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:45:22 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/22 00:53:04 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//donne l'indice du prochaine ' ou "" si pas trouver alors -42
int	quote_chr(char *str, int i)
{
	char	quote;
	
	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
	{
		i++;
	}
	if (str[i])
		return (i);
	else
		return (-42);
}

//verifie si il y a bien des doublons de " ou ', si un seul alors probleme
int	quotes_syntax(char *line)
{
	int	i;
	int add_index;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			add_index = quote_chr(line, i);
			if (add_index == -42)
				return (1);
			i = add_index;
		}
		i++;
	}
	return (0);
}

// verifie si premier caractere est pipe ou si dernier caractere est pipe
int	pipe_syntax(char *line)
{
	int	i;
	bool flag;
    
	flag = false;
	i = -1;
	if (line[0] == '|')
		return (1);
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = quote_chr(line, i);
		if (line[i] && line[i] == '|')
		{
			while ((line[i] && line[i] == ' ') || line[i] && line[i] == '|')
				i++;
			if (line[i] == '\0')
				return(1);
		}
	}
	return (0);
}

int	redirections_syntax(char *line)
{
	int	i;
	char quotes;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			quotes = line[i++];
			while (line[i] != quotes)
				i++;
			i++;
		}
		if (ft_strchr("<>", line[i]))
		{
			while (line[i] && ft_strchr("<> |", line[i]))
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	pre_parsing(char *line)
{
		if(quotes_syntax(line))
		{
			printf("Quotes are not close");
			return (1);
		}
		if(pipe_syntax(line))
		{
			printf("Need cmd after pipe");
			return (1);
		}
		if (redirections_syntax(line))
		{
			printf("problem redirections");
		}
		return (0);
}
