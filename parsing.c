/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:45:22 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/12 13:45:19 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (0);
}


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
	char	*line;
	int	i;
	bool flag;
    
	flag = false;
	i = -1;
	if (line[0] == '|')
		return (1);
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = quote_chr(data, i);
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






