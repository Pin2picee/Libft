/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 23:47:15 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	control_d_herdoc(char *buf_line, char *wanted, t_node *node)
{
	if (!buf_line)
	{
		write(2, "Minishell: warning: here-document at line 1 "
			"delimited by end-of-file (wanted)\n", 79);
		if (node->hd)
			free(node->hd);
		node->hd = NULL;
		node->hd = ft_calloc(1, 1);
		return (1);
	}
	return (0);
}

void	control_d(t_minishell *data)
{
	if (!data->line)
	{
		free_env_vars(data);
		if (data->export)
			free_tab(data->export);
		if (data->envp)
			free_tab(data->envp);
		clear_history();
		write(1, "exit\n", 5);
		exit(errno);
	}
}

// verifie si entre alors que ligne vide
int	empty_line(t_minishell *data)
{
	if (data->line[0] == '\0')
	{
		free(data->line);
		return (1);
	}
	return (0);
}

void	print_prompt(t_minishell *data)
{
	data->prompt = NULL;
	data->prompt = get_prompt();
	data->line = readline("👾🐉$> ");
	free(data->prompt);
	data->prompt = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	(void)argv;
	if (argc != 1)
		return (perror("Error\n"), 1);
	setups_signals();
	setup(&data, envp, -1);
	while (1)
	{
		print_prompt(&data);
		control_d(&data);
		if (empty_line(&data))
			continue ;
		add_history(data.line);
		if (!parsing(&data))
			ft_exec(&data);
		ft_reset(&data);
	}
	free_all(&data);
	return (0);
}
