/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 01:04:31 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// verifie si ctrl+d dans un here_doc je sais je suis trop chaud
int	control_d_herdoc(char *buf_line, char *wanted, t_node *node)
{
	if (!buf_line)
	{
		ft_putstr_fd("Minishell: warning: here-document at line 1 delimited by end-of-file (wanted)\n", 2);
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
		data->prompt = get_prompt();// recup le prompt
		data->line = readline(data->prompt);// un input avec l'affichage du prompt
		free(data->prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	int	i = 0;//test
	
	(void)argv;
	if (argc != 1)
		return (perror("Error\n"), 1);
	setup(&data, envp, 0);
	while (1)
	{
		print_prompt(&data);
		control_d(&data);
		if (empty_line(&data))
			continue ;
		add_history(data.line);
		if (!parsing(&data))
			ft_exec(&data);
		ft_reset(&data);//renitialise la data.line / les noeuds et les free
	}
	free_all(&data);// free tous ma data et mes noeuds .
	return (0);
}
