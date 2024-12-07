/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:59:14 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/06 22:31:02 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	init_node(t_node *node)
{
	if (node == NULL)
		return;
	node->hd = NULL;
	node->command = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	node->next = NULL;
	node->split = NULL;
	node->cmd_path = NULL;
	
}

void	init_data(t_minishell *data)
{
	data->envp = NULL;
	data->export = NULL;
	data->line = NULL;
	data->exit_code = 0;
	data->prompt = NULL;
	data->var = NULL;
	data->start_node = NULL;
	data->pid = -2;
	data->status = 0;
	data->fd_stdin = 0;
	data->fd_stdout = 1;
	data->child_pid = 0;
}

