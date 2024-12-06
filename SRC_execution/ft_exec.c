/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:34:32 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/06 11:22:22 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		manage_status(t_minishell *data)
{
	int signal_num;
	
	if (WIFEXITED(data->status)) 
	{
		// Si le fils s'est terminé normalement
		data->exit_code = WEXITSTATUS(data->status);
	}
	else if (WIFSIGNALED(data->status))
	{
		// Si le fils a été tué par un signal
		signal_num = WTERMSIG(data->status);
		if (signal_num == SIGINT) 
			data->exit_code = 130;
	}
}

static void	reset_data(t_minishell *data)
{
	data->pipe_tab = NULL;
	data->pid = -2;
	data->status = 0;
	data->child_pid = 0;
	dup2(0, data->fd_stdin);
	dup2(1, data->fd_stdout);
}

int	manage_execve(t_minishell *data, char *cmd, t_node *current)
{
	int	i;
	int	found;
	char	**all_path;
	char	*cmd_path;
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
	all_path = ft_split(curr_env->value, ':');
	i = -1;
	while(all_path[++i])
	{
		cmd_path = ft_calloc(sizeof(char), ft_strlen(all_path[i]) + ft_strlen(cmd) + 2);
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
	execve(current->cmd_path, current->split, data->envp);
	return (1);
}

int	manage_builtin(t_minishell *data, t_node *node, char *cmd) // To add to .h
{
	if (strcmp(cmd, "echo") == 0)
		 	ft_echo(node);
	else if (strcmp(cmd, "cd") == 0)
	 	ft_cd(data, node);
	if (strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (strcmp(cmd, "export") == 0)
	 	ft_export(node, 1);
	else if (strcmp(cmd, "unset") == 0)
	 	ft_unset(node);
	else if (strcmp(cmd, "env") == 0)
	 	ft_env(data);
	else if (strcmp(cmd, "exit") == 0)
		ft_exit(node);
	if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0 ||
		strcmp(cmd, "pwd") == 0 || strcmp(cmd, "export") == 0 ||
		strcmp(cmd, "unset") == 0 || strcmp(cmd, "env") == 0 ||
		strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void    manage_fork(t_minishell *data, t_node **node, pid_t *pid) // To add to .h / manage_pipe_and_fork
{
	if (data->node_nbr == 1 && manage_builtin(data, *node, (*node)->split[0]))
		return ;
	while (*node && *pid != 0)
	{
		if (*pid > 0)
			(*node) = (*node)->next;
		if (*pid > 0 && !(*node))
			return;
		if (*pid != 0)
		{
			*pid = fork();
			if (*pid == 0)
			{
				manage_pipe(data, &data->current_node);
				if (!(*node)->split)
					exit(0);
				if (manage_builtin(data, *node, (*node)->split[0]))
					exit(0);
				else if (manage_execve(data, data->current_node->split[0], data->current_node))
					exit (0) ; // Gestion d'erreur
				else if (!access((*node)->split[0], F_OK))
					execve((*node)->split[0], (*node)->split, data->envp);// dans le cas d'un executable
				printf("Minishell : %s : command not found .\n", (*node)->split[0]);
				exit(127);
			}
		}
		if (*pid == -1)
			exit(0); // Gestion d'erreur
	}
}

void	ft_exec(t_minishell *data)
{
	data->current_node = data->start_node;
	manage_pipe_parent(data, 0);
	manage_fork(data, &data->current_node, &data->pid);
	manage_pipe_parent(data, 1);
	while ((data->child_pid = waitpid(-1, &data->status, 0)) > 0);
	manage_status(data);
	if (data->node_nbr > 1)
		free(data->pipe_tab);
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
