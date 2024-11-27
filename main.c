/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/27 22:08:14 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	t_minishell	data;
	int	i = 0;//test
	
	(void)argv;
	if (argc != 1)
		return (perror("Error\n"), 1);
	setups_signals();
	init_env(&data, envp);
	print_art();// fonction qui affiche le debut de  notre minishell en beaute
	while (1)
	{
		data.prompt = get_prompt();// recup le prompt
		data.line = readline(data.prompt);// un input avec l'affichage du prompt
		free(data.prompt);
		if (data.line[0] == '\0')
		{
			free(data.line);
			continue ;
		}
			add_history(data.line);
			if (!parsing(&data))
			{
				ft_export(data.start_node);
				printf("good\n");
				//execution(&data);
			}
			ft_reset(&data);//renitialise la data.line / les noeuds et les free
	}
	free_all(&data);// free tous ma data et mes noeuds .
	return (0);
}
