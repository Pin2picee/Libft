/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:17:07 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/06 17:10:54 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_minishell *data, int i, int j, int option)
{
	if (!data->current_node->split[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strncmp(data->current_node->split[1], "-n", 2) == 0)
	{
		while (data->current_node->split[1] && data->current_node->split[1][++j] == 'n');
		if (data->current_node->split[1][j] == '\0' && data->current_node->split[1][j - 1] == 'n')
				option = 1;
	}
	while(data->current_node->split[++i + option])
	{
		ft_putstr_fd(data->current_node->split[i + option], data->current_node->fd_out);
		if (!data->current_node->split[i + 1 + option])
		{
			if (option == 0)
				ft_putstr_fd("\n", data->current_node->fd_out);
			break ;
		}
		ft_putstr_fd(" ", data->current_node->fd_out);
	}
}
