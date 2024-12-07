/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:49:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 00:16:44 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    create_hd(t_minishell *data)
{
	t_node  *current;

	current = data->start_node;
	while(current)
	{
		if (current->hd)
		{
			if ((current->fd_in = open("hd", O_CREAT | O_WRONLY | O_RDONLY, 0666)) < 0)
				perror("Minishell : Permission denied");
			ft_putstr_fd(current->hd, current->fd_in);
			close(current->fd_in);
		}
		current = current->next;
	}
}
void	unlink_hd(t_minishell *data)
{
	t_node	*current;

	current = data->start_node;
	while(current)
	{
		if (current->hd)
		{
			if (unlink("hd"))
			{
				perror("unlink");
			}
		}
		current = current->next;
	}
}
