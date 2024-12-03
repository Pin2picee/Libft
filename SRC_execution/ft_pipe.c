/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhallou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:11:23 by nhallou           #+#    #+#             */
/*   Updated: 2024/11/14 17:11:24 by nhallou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    close_pipe_fork(t_minishell *data, t_node *node, int param, int i) // To add to .h
{
    i = 0;
    if (param == 1)
    {
        close(data->pipe_tab[node->pos - 1][0]);
        while (++i <= data->node_nbr - 2)
        {
            close(data->pipe_tab[i][0]);
            close(data->pipe_tab[i][1]);
        }
    }
    else if (param == 2)
    {
        close(data->pipe_tab[(node->pos - 2)][1]);
        close(data->pipe_tab[(node->pos - 1)][0]);
        while (i <= data->node_nbr - 2)
        {
            if (i == node->pos - 2)
            {
                i += 2;
                continue;
            }
            close(data->pipe_tab[i][0]);
            close(data->pipe_tab[i][1]);
            i++;
        }
    }
    else if (param == 3)
    {

        close(data->pipe_tab[node->pos - 2][1]);
        while (i < node->pos - 2)
        {
            close(data->pipe_tab[i][0]);
            close(data->pipe_tab[i][1]);
            i++;
        }
    }
}

void    manage_pipe_fork(t_minishell *data, t_node **node) // To add to .h / manage_pipe_and_fork
{
    if (data->node_nbr > 1)
    {
        if ((*node) == data->start_node)
        {
            close_pipe_fork(data, (*node), 1, 0);
            dup2(data->pipe_tab[((*node)->pos - 1)][1], 1);
            close(data->pipe_tab[((*node)->pos - 1)][1]);
        }
        else if ((*node)->next && (*node) != data->start_node)
        {
            close_pipe_fork(data, (*node), 2, 0);
            dup2(data->pipe_tab[((*node)->pos - 2)][0], 0);
            dup2(data->pipe_tab[((*node)->pos - 1)][1], 1);
            close(data->pipe_tab[((*node)->pos - 2)][0]);
            close(data->pipe_tab[((*node)->pos - 1)][1]);
        }
        else if     (!(*node)->next)
        {
            close_pipe_fork(data, (*node), 3, 0);
            dup2(data->pipe_tab[((*node)->pos - 2)][0], 0);
            close(data->pipe_tab[((*node)->pos - 2)][0]);
        }
    }
    dup2((*node)->fd_in, 0);
    dup2((*node)->fd_out, 1);
    //close((*node)->fd_in);
    //close((*node)->fd_out);
}

void    create_fork(t_minishell *data, t_node **node, pid_t *pid) // To add to .h / manage_pipe_and_fork
{
    while (*node && *pid != 0)
    {
        if (*pid > 0)
            (*node) = (*node)->next;
        if (*pid > 0 && !(*node))
            return;
        if (*pid != 0)
            *pid = fork();
        if (*pid == -1)
            exit(0);
        usleep(50);
    }
}

void manage_pipe_parent(t_minishell *data, int param) // To add  to .h / manage_pipe_tab
{
    int i;

    i = 0;
    if (param == 0 && data->node_nbr > 1)
    {
        data->pipe_tab = calloc((data->node_nbr - 1), sizeof(int[2]));
        while (i < data->node_nbr - 1)
        {
            if (pipe(data->pipe_tab[i]) == -1)
            {
                perror("Pipe error");
                exit(EXIT_FAILURE);
            }
            i++;
        }
    }
    else if (param == 1 && data->node_nbr > 1)
    {
        while (i < data->node_nbr - 1)
        {
            close(data->pipe_tab[i][0]);
            close(data->pipe_tab[i][1]);
            i++;
        }
    }
}
