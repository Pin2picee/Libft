/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:34:32 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/06 18:11:39 by abelmoha         ###   ########.fr       */
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

void		manage_status_reset_data(t_minishell *data)
{
	int signal_num;

	if (WIFEXITED(data->status)) 
	{
		data->exit_code = WEXITSTATUS(data->status);
	}
	else if (WIFSIGNALED(data->status))
	{
		signal_num = WTERMSIG(data->status);
		if (signal_num == SIGINT) 
			data->exit_code = 130;
	}
}

char	*check_cmd_path(t_minishell *data, char *path, char **a_pth, int *found)
{
	int	i;

	i = -1;
	while(a_pth[++i])
	{
		path = ft_calloc(sizeof(char), ft_strlen(a_pth[i]) +
			ft_strlen(data->current_node->split[0]) + 2);
		path = strcat(path, a_pth[i]);
		path = strcat(path, "/");
		path = strcat(path, data->current_node->split[0]);
		*found = access(path, F_OK);
		if (*found == 0)
		{
			data->current_node->cmd_path = path;
			break;
		}
		free(path);
		data->current_node->cmd_path = NULL;
	}
	return (path);
}

int	manage_execve(t_minishell *data)
{
	int	i;
	int	found;
	char	**a_pth;
	char	*path;
	t_env	*curr_env;

	i = -1;
	found = -1;
	curr_env = data->var;
	while (curr_env && ft_strncmp(curr_env->key, "PATH", 4) != 0)
	{
		if (!curr_env)
			return (0);
		curr_env = curr_env->next;
	}
	a_pth = ft_split(curr_env->value, ':');
	path = check_cmd_path(data, path, a_pth, &found);
	i = -1;
	while(a_pth[++i])
		free(a_pth[i]);
	free(a_pth);
	if (found != 0)
		return (0);
	execve(path, data->current_node->split, data->envp);
	return (1);
}

int	manage_builtin(t_minishell *data)
{
	if (strcmp(data->current_node->split[0], "echo") == 0)
		 	ft_echo(data, 0, 0 , 0);
	else if (strcmp(data->current_node->split[0], "cd") == 0)
	 	ft_cd(data, data->current_node);
	if (strcmp(data->current_node->split[0], "pwd") == 0)
		ft_pwd();
	else if (strcmp(data->current_node->split[0], "export") == 0)
	 	ft_export(data->current_node, 1);
	else if (strcmp(data->current_node->split[0], "unset") == 0)
	 	ft_unset(data->current_node);
	else if (strcmp(data->current_node->split[0], "env") == 0)
	 	ft_env(data);
	else if (strcmp(data->current_node->split[0], "exit") == 0)
		ft_exit(data->current_node);
	if (strcmp(data->current_node->split[0], "echo") == 0 ||
		strcmp(data->current_node->split[0], "cd") == 0 ||
		strcmp(data->current_node->split[0], "pwd") == 0 ||
		strcmp(data->current_node->split[0], "export") == 0 ||
		strcmp(data->current_node->split[0], "unset") == 0 ||
		strcmp(data->current_node->split[0], "env") == 0 ||
		strcmp(data->current_node->split[0], "exit") == 0)
		return (1);
	return (0);
}

void    manage_fork(t_minishell *data)
{
	if (data->node_nbr == 1 && manage_builtin(data))
		return ;
	while (data->current_node && data->pid != 0)
	{
		if (data->pid > 0)
			data->current_node = data->current_node->next;
		if (data->pid > 0 && !data->current_node)
			return;
		if (data->pid != 0)
		{
			data->pid = fork();
			if (data->pid == 0)
			{
				manage_pipe(data);
				if (!data->current_node->split)
					exit(0);
				if (manage_builtin(data))
					exit(0);
				else if (manage_execve(data))
					exit (0) ;
				else if (!access(data->current_node->split[0], F_OK))
					execve(data->current_node->split[0],data->current_node->split, data->envp);
				printf("%s : command not found .\n", data->current_node->split[0]);
				exit(127);
			}
		}
		if (data->pid == -1)
			exit(0);
	}
}

void	ft_exec(t_minishell *data)
{
	data->current_node = data->start_node;
	create_hd(data);
	manage_pipe_parent(data, 0, -1);
	manage_fork(data);
	manage_pipe_parent(data, 1, -1);
	unlink_hd(data);
	while ((data->child_pid = waitpid(-1, &data->status, 0)) > 0);
	manage_status_reset_data(data);
	reset_data(data);
	return ;
}

/*
set follow-fork-mode parent
b ft_exec
r
pwd | pwd
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
