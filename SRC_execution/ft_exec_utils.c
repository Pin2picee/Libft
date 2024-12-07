/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:02:04 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/07 20:30:13 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_builtin(t_minishell *data)
{
	if (strcmp(data->current_node->split[0], "echo") == 0
		|| strcmp(data->current_node->split[0], "cd") == 0
		|| strcmp(data->current_node->split[0], "pwd") == 0
		|| strcmp(data->current_node->split[0], "export") == 0
		|| strcmp(data->current_node->split[0], "unset") == 0
		|| strcmp(data->current_node->split[0], "env") == 0
		|| strcmp(data->current_node->split[0], "exit") == 0)
		return (1);
	return (0);
}

int	child_handler(t_minishell *data, int exit_code)
{
	manage_pipe(data);
	if (data->current_node->split == NULL)
		return (free_all(data), exit(127), 1);
	if (manage_builtin(data))
		return (free_all(data), exit(exit_code), 1);
	else if (manage_execve(data, -1))
		return (perror("Minishell "), free_all(data), exit(0), 0);
	else if (!access(data->current_node->split[0], F_OK)
		&& ft_strncmp(data->current_node->split[0], "foo", 4200))
		execve(data->current_node->split[0],
			data->current_node->split, data->envp);
	else
		return (ft_putstr_fd(data->current_node->split[0], 2), free_all(data),
			ft_putstr_fd(" : cmd not found !\n", 2), exit(127), 0);
}

void	manage_status_reset_data(t_minishell *data)
{
	int	signal_num;

	if (WIFEXITED(data->status))
		data->exit_code = WEXITSTATUS(data->status);
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
	while (a_pth[++i])
	{
		path = ft_calloc(sizeof(char), ft_strlen(a_pth[i])
				+ ft_strlen(data->current_node->split[0]) + 2);
		path = strcat(path, a_pth[i]);
		path = strcat(path, "/");
		path = strcat(path, data->current_node->split[0]);
		*found = access(path, F_OK);
		if (*found == 0)
		{
			data->current_node->cmd_path = path;
			break ;
		}
		free(path);
		data->current_node->cmd_path = NULL;
	}
	return (path);
}
