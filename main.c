/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/02 16:44:19 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// verifie si ctrl+d free tous
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
		ft_SHLVL(data);
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
	setup(&data, envp);
	while (1)
	{
		print_prompt(&data);
		control_d(&data);
		if (empty_line(&data))
			continue ;
		add_history(data.line);
		if (!parsing(&data))
		{
			/*if (!ft_strncmp(data.start_node->split[0], "export", ft_strlen(data.start_node->split[0])))
				ft_export(data.start_node);
			else if (!ft_strncmp(data.start_node->split[0], "env", ft_strlen(data.start_node->split[0])))
				ft_env(&data);
			else if (!ft_strncmp(data.start_node->split[0], "unset", ft_strlen(data.start_node->split[0])))
				ft_unset(data.start_node);
			else if (!ft_strncmp(data.start_node->split[0], "pwd", ft_strlen(data.start_node->split[0])))
				ft_pwd();*/
			ft_pre_exec(&data);
		}
		ft_reset(&data);//renitialise la data.line / les noeuds et les free
	}
	free_all(&data);// free tous ma data et mes noeuds .
	return (0);
}
