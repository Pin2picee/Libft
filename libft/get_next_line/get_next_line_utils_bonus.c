/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:29:59 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/21 15:34:46 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

int	found_newline(t_listes *stash)
{
	int			i;
	t_listes	*current;

	if (stash == NULL)
		return (0);
	current = last_maillon(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_listes	*last_maillon(t_listes *stash)
{
	t_listes	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

// generate_line compte les caracteres stocke dans
// chaque maillon puis les additione pour malloc la ligne a envoyez
// genere et malloc la ligne en parcourant chaque
// copy de mon buff sur chaque maillon
void	generate_line(char **line, t_listes *stash)
{
	int	i_maillon;
	int	len;

	len = 0;
	while (stash)
	{
		i_maillon = 0;
		while (stash->content[i_maillon])
		{
			if (stash->content[i_maillon] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i_maillon++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stash(t_listes *stash)
{
	t_listes	*current;
	t_listes	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
