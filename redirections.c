/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/13 19:58:04 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirectiom(char *name_f, char c)
{
	int	i;
	bool append;
	bool hd;
	
	if(name_f[i] == '>' && name_f[i] == c)
		append = true;
	if (name_f[i] == '<' && name_f[i++] == c)
		hd = true;
	while (name_f[i])
	{
		if (name_f[i])
		i++;
	}	
}

char	*redirections_handler(char *command)
{
	int	i;
	
	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
			i = quote_chr(command, i) + 1;
		if (command[i] == '>')
		{
			i++;
			redirection(command + i, command[i]);
		}
		i++;
	}
}
/**
 * 
*/