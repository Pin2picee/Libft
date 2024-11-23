/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:09:31 by Pin2picee         #+#    #+#             */
/*   Updated: 2024/11/23 19:29:04 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s, int size)
{
	int		i;
	char	*dst;

	i = 0;
    if (size < 1)
        return (NULL);
	dst = malloc(sizeof(char) * (size) + 1);
	if (dst == NULL)
		return (NULL);
	while (s[i] && i < size)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
// la fonction malloc une chaine jusqu'a une certaine taille puis la copie jusqu'a la taille . 
