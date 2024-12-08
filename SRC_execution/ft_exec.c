/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:34:32 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/08 15:02:03 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_data(t_minishell *data)
{
	data->current_node = data->start_node;
	while (data->current_node)
	{
		if (data->current_node != NULL && data->current_node->cmd_path != NULL)
		{
			free(data->current_node->cmd_path);
			data->current_node->cmd_path = NULL;
		}
		if (data->current_node->next != NULL)
			data->current_node = data->current_node->next;
		else
			break ;
	}
	if (data->node_nbr > 1 && data->pipe_tab != NULL)
		free(data->pipe_tab);
	data->pipe_tab = NULL;
	data->pid = -2;
	data->status = 0;
	data->child_pid = 0;
	dup2(0, data->fd_stdin);
	dup2(1, data->fd_stdout);
}

int	manage_execve(t_minishell *data, int i)
{
	int		found;
	char	**a_pth;
	char	*path;
	t_env	*curr_env;

	found = -1;
	curr_env = data->var;
	while (curr_env && ft_strncmp(curr_env->key, "PATH", 4) != 0)
	{
		if (!curr_env)
			return (0);
		curr_env = curr_env->next;
	}
	if (curr_env == NULL)
		return (0);
	a_pth = ft_split(curr_env->value, ':');
	path = check_cmd_path(data, path, a_pth, &found);
	i = -1;
	while (a_pth && a_pth[++i])
		free(a_pth[i]);
	free(a_pth);
	if (found != 0)
		return (0);
	execve(path, data->current_node->split, data->envp);
	return (1);
}

int	manage_builtin(t_minishell *data)
{
	if (data->pid != 0 && data->current_node->split == NULL)
		return (ft_putstr_fd("command not found : ''\n", 2), 0);
	else if (data->pid == 0 && data->current_node->split == NULL)
		exit(127);
	if (ft_strcmp(data->current_node->split[0], "echo") == 0)
		ft_echo(data, 0, 0, 0);
	else if (ft_strcmp(data->current_node->split[0], "cd") == 0)
		ft_cd(data, data->current_node, 0);
	if (ft_strcmp(data->current_node->split[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->current_node->split[0], "export") == 0)
		ft_export(data->current_node, 1, 0);
	else if (ft_strcmp(data->current_node->split[0], "unset") == 0)
		ft_unset(data->current_node);
	else if (ft_strcmp(data->current_node->split[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->current_node->split[0], "exit") == 0)
		ft_exit(data->current_node);
	return (verif_builtin(data));
}

int	manage_fork(t_minishell *data, int exit_code)
{
	if (data->node_nbr == 1 && manage_builtin(data))
		return (0);
	while (data->current_node && data->pid != 0)
	{
		if (data->pid > 0 && !data->current_node)
			return (0);
		if (data->pid != 0)
		{
			data->pid = fork();
			if (data->pid == 0)
				child_handler(data, exit_code);
		}
		if (data->pid > 0)
			data->current_node = data->current_node->next;
		if (data->pid == -1)
			exit(0);
	}
}

void	ft_exec(t_minishell *data)
{
	int	status;

	data->current_node = data->start_node;
	create_hd(data);
	manage_pipe_parent(data, 0, -1);
	manage_fork(data, data->exit_code);
	manage_pipe_parent(data, 1, -1);
	data->child_pid = waitpid(-1, &status, 0);
	while (data->child_pid > 0)
	{
		data->status = status;
		data->child_pid = waitpid(-1, &status, 0);
	}
	manage_status_reset_data(data);
	unlink_hd(data);
	reset_data(data);
	return ;
}
