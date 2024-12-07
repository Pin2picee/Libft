/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:11:23 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/07 19:45:28 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe_case_2(t_minishell *data, int i)
{
	close(data->pipe_tab[(data->current_node->pos - 2)][1]);
	close(data->pipe_tab[(data->current_node->pos - 1)][0]);
	while (i <= data->node_nbr - 2)
	{
		if (i == data->current_node->pos - 2)
		{
			i += 2;
			continue ;
		}
		close(data->pipe_tab[i][0]);
		close(data->pipe_tab[i][1]);
		i++;
	}
}

void	close_pipe(t_minishell *data, int param, int i)
{
	if (param == 1)
	{
		close(data->pipe_tab[data->current_node->pos - 1][0]);
		while (++i <= data->node_nbr - 2)
		{
			close(data->pipe_tab[i][0]);
			close(data->pipe_tab[i][1]);
		}
	}
	else if (param == 2)
		close_pipe_case_2(data, i);
	else if (param == 3)
	{
		close(data->pipe_tab[data->current_node->pos - 2][1]);
		while (i < data->current_node->pos - 2)
		{
			close(data->pipe_tab[i][0]);
			close(data->pipe_tab[i][1]);
			i++;
		}
	}
}

void	manage_redirections(t_minishell *data)
{
	if (data->current_node->fd_in < 0 || data->current_node->fd_out < 0)
	{
		free_all(data);
		exit(data->exit_code);
	}
	if (data->current_node->hd)
		data->current_node->fd_in = open("hd", O_RDONLY);
	if ((dup2(data->current_node->fd_in, 0) < 0)
		|| (dup2(data->current_node->fd_out, 1) < 0))
		exit(data->exit_code);
	if (data->current_node->hd)
		close(data->current_node->fd_in);
}

void	manage_pipe(t_minishell *data)
{
	if (data->node_nbr > 1)
	{
		if (data->current_node == data->start_node)
		{
			close_pipe(data, 1, 0);
			dup2(data->pipe_tab[(data->current_node->pos - 1)][1], 1);
			close(data->pipe_tab[(data->current_node->pos - 1)][1]);
		}
		else if (data->current_node->next
			&& data->current_node != data->start_node)
		{
			close_pipe(data, 2, 0);
			dup2(data->pipe_tab[(data->current_node->pos - 2)][0], 0);
			dup2(data->pipe_tab[(data->current_node->pos - 1)][1], 1);
			close(data->pipe_tab[(data->current_node->pos - 2)][0]);
			close(data->pipe_tab[(data->current_node->pos - 1)][1]);
		}
		else if (!data->current_node->next)
		{
			close_pipe(data, 3, 0);
			dup2(data->pipe_tab[(data->current_node->pos - 2)][0], 0);
			close(data->pipe_tab[(data->current_node->pos - 2)][0]);
		}
	}
	manage_redirections(data);
}

void	manage_pipe_parent(t_minishell *data, int param, int i)
{
	if (data->node_nbr > 1 && data->pid != 0)
	{
		if (param == 0 && data->node_nbr > 1)
		{
			data->pipe_tab = ft_calloc(data->node_nbr - 1, 32);
			while (++i < data->node_nbr - 1)
			{
				if (pipe(data->pipe_tab[i]) == -1)
				{
					perror("\033[34mPipe error\033[0m");
					exit(EXIT_FAILURE);
				}
			}
		}
		else if (param == 1 && data->node_nbr > 1)
		{
			while (++i < data->node_nbr - 1)
			{
				close(data->pipe_tab[i][0]);
				close(data->pipe_tab[i][1]);
			}
		}
	}
}
