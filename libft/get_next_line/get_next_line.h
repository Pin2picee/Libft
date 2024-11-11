/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:50:00 by abelmoha          #+#    #+#             */
/*   Updated: 2024/09/23 19:59:18 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h> // enlever

//     Mon buffer temp
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

// ma structure que je vais chainer pour chaque liste

typedef struct s_liste
{
	char			*content;
	struct s_liste	*next;
}				t_liste;

// utils

void	extract_line(t_liste *stash, char **line);
void	generate_line(char **line, t_liste *stash);
t_liste	*last_maillon(t_liste *stash);
int		found_newline(t_liste *stash);
int		ft_strlenn(const char *str);
void	free_stash(t_liste *stash);

// principal
char	*get_next_line(int fd);
void	buff_to_stash(t_liste **stash, char *buff, int lettre_lu);
void	read_and_stash(t_liste **stash, int fd);

void	clean_stash(t_liste **stash);

#endif