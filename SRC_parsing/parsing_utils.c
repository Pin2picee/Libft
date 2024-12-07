/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:45:22 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 19:19:30 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	quotes_syntax(char *line)
{
	int	i;
	int	add_index;

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

int	pipe_syntax(char *line, int i, bool flag)
{
	if (!line || line[0] == '|')
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] && line[i] == '|')
		return (1);
	i = 0;
	while (i < ft_strlen(line) && line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i = quote_chr(line, i);
			continue ;
		}
		if (line[i] && line[i] == '|')
		{
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '\0' || line [i] == '|')
				return (1);
		}
	}
	return (0);
}

int	redirections_syntax(char *line)
{
	int		i;
	char	quotes;

	i = 0;
	while (i < ft_strlen(line) && line[i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			i = quote_chr(line, i) + 1;
			continue ;
		}
		if (line[i] && ft_strchr("<>", line[i]))
		{
			while (line[i] && ft_strchr("<> |", line[i]))
				i++;
			if (!line[i])
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	pre_parsing(char *line)
{
	if (line[0] == '\0')
		return (1);
	if (quotes_syntax(line))
	{
		printf("Quotes are not close\n");
		return (1);
	}
	if (pipe_syntax(line, 0, false))
	{
		printf("Need cmd after pipe\n");
		return (1);
	}
	if (redirections_syntax(line))
	{
		printf("problem redirections\n");
		return (1);
	}
	return (0);
}
