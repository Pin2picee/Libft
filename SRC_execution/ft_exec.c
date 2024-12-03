/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhallou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:34:32 by nhallou           #+#    #+#             */
/*   Updated: 2024/11/19 15:34:33 by nhallou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_execve(t_minishell *data, char *cmd, t_node *current)
{
	int	i;
	int	found;
	char	**all_path;
	char	*cmd_path;
	t_env	*curr_env;

	i = -1;
	found = -1;
	
	curr_env = data->var;
	while (curr_env && strncmp(curr_env->key, "PATH", 4) != 0)
	{
		if (!curr_env)
			return ;
		curr_env = curr_env->next;
	}
	all_path = ft_split(curr_env->value, ':');
	i = -1;
	while(all_path[++i])
	{
		cmd_path = ft_calloc(sizeof(char), strlen(all_path[i]) + strlen(cmd) + 2);
		cmd_path = strcat(cmd_path, all_path[i]);
		cmd_path = strcat(cmd_path, "/");
		cmd_path = strcat(cmd_path, cmd);
		found = access(cmd_path, F_OK);
		if (found == 0)
			break;
		free(cmd_path);
	}
	current->cmd_path = cmd_path;
	i = -1;
	while(all_path[++i])
		free(all_path[i]);
	free(all_path);
	if (found != 0)
		return ;
	execve(current->cmd_path, current->split, data->envp);
}

int	check_builtin(t_node *node, char *cmd) // To add to .h
{
	// if (strcmp(cmd, "echo") == 0)
	// 	ft_echo()
	// else if (strcmp(cmd, "cd") == 0)
	// 	ft_cd();
	// else if (strcmp(cmd, "pwd") == 0)
	// 	ft_pwd();
	// else if (strcmp(cmd, "export") == 0)
	// 	ft_export();
	// else if (strcmp(cmd, "unset") == 0)
	// 	ft_unset();
	// else if (strcmp(cmd, "env") == 0)
	// 	ft_env
	if (strcmp(cmd, "exit") == 0)
		ft_exit(node);
	else
		return (0);
	return (1);
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
		{
			if (check_builtin(*node, (*node)->split[0]) == 1)
			{
				(*node) = (*node)->next;
				continue ;
			}
			*pid = fork();
		}
		if (*pid == -1)
            exit(0);
        usleep(50);
    }
}

void	ft_exec(t_minishell *data)
{
	int	child_pid;

	child_pid = 0;
	data->current_node = data->start_node;
	if (data->node_nbr > 1)
		manage_pipe_parent(data, 0);
	create_fork(data, &data->current_node, &data->pid);
	if (data->pid != 0 && data->node_nbr > 1)
		manage_pipe_parent(data, 1);
	else if (data->pid == 0)
	{
		manage_pipe_fork(data, &data->current_node);
		check_execve(data, data->current_node->split[0], data->current_node);
	}
	while ((child_pid = waitpid(-1, &data->status, 0)) > 0);
	if (data->node_nbr > 1)
		free(data->pipe_tab);
	data->pipe_tab = NULL;
	data->pid = -2;
	data->status = 0;
	dup2(0, data->fd_stdin);
	dup2(1, data->fd_stdout);
	return ;
}

/*
set follow-fork-mode parent
b ft_pre_exec
r
ls | ls
define hook-stop
refresh
end
refresh
n
n

set detach-on-fork off
set follow-fork-mode child

*/

/*
display data->pipe_tab[0]
display data->pipe_tab[1]
display node->pos

*/

/*
display i
display node->pos
display data->pipe_tab[node->pos - 1]
display data->pipe_tab[i]

*/

// set follow-fork-mode child

// display data->pipe_tab[0]@4

/*
define hook-stop
info inferiors
end

*/

// set detach-on-fork off
// show follow-fork-mode