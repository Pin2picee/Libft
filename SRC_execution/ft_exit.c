/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:22:09 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/07 20:35:06 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_and_exit(t_node *node, int exit_code)
{
	free_all(node->data);
	exit(exit_code);
}

void	ft_exit_handler(t_node *node, int tmp_nb)
{
	if (node->data->start_node->next == NULL)
		ft_printf("exit\n");
	if (!(node->split[1]) && node->data->start_node->next == NULL)
	{
		free_all(node->data);
		exit(0);
	}
	else if (!str_is_digit(node->split[1]))
	{
		if (atoi(node->split[1]) < 0)
			exit (atoi(node->split[1]));
		printf("minishell: exit %s: numeric argument is required\n",
			node->split[1]);
		free_and_exit(node, 2);
	}
	else if (node->split[2])
	{
		printf("minishell: exit: too many arguments\n");
		tmp_nb = ft_atoi(node->split[1]);
		free_and_exit(node, tmp_nb);
	}
	tmp_nb = ft_atoi(node->split[1]);
	free_and_exit(node, tmp_nb);
}

void	ft_exit(t_node *node)
{
	ft_exit_handler(node, 0);
}
