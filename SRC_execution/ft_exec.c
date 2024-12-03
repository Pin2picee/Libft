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

int	check_execve(t_minishell *data, char *cmd, t_node *current)
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
			return (0);
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
		return (0);
	return (1);
}

int	check_builtin(t_node *node, char *cmd) // To add to .h
{
	if (strcmp(cmd, "echo") == 0)
		node->cmd_type = ECHO;
	else if (strcmp(cmd, "cd") == 0)
		node->cmd_type = CD;
	else if (strcmp(cmd, "pwd") == 0)
		node->cmd_type = PWD;
	else if (strcmp(cmd, "export") == 0)
		node->cmd_type = EXPORT;
	else if (strcmp(cmd, "unset") == 0)
		node->cmd_type = UNSET;
	else if (strcmp(cmd, "env") == 0)
		node->cmd_type = ENV;
	else if (strcmp(cmd, "exit") == 0)
		node->cmd_type = EXIT;
	else
		return (0);
	return (1);
}

void	ft_exec(t_minishell *data, t_node *node) // To add to .h
{
	int type;
	int	i;

	i = 0;
	manage_pipe_fork(data, &node);
	if (check_builtin(node, node->split[0]) == 1)
		exit(0);
	else if (check_execve(data, node->split[0], node) == 1)
		execve(node->cmd_path, node->split, data->envp);
	else
		exit(0);
}

int	ft_pre_exec(t_minishell *data)
{
	data->current_node = data->start_node;
	if (data->node_nbr > 1)
		manage_pipe_parent(data, 0);
	create_fork(data, &data->current_node, &data->pid);
	if (data->pid != 0 && data->node_nbr > 1)
		manage_pipe_parent(data, 1);
	else if (data->pid == 0)
		ft_exec(data, data->current_node);
	waitpid(-1, &data->status, 0);
	if (data->node_nbr > 1)
		free(data->pipe_tab);
	data->pipe_tab = NULL;
	data->pid = -2;
	dup2(0, data->fd_stdin);
	dup2(1, data->fd_stdout);
	return (0);
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