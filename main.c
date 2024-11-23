/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pin2picee <Pin2picee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/23 23:12:56 by Pin2picee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	t_minishell	data;
	
	(void)argv;
	if (argc != 1)
		return (perror("Error\n"), 1);
	setup_signals();//fonction qui configure le signal des touche interactive qui au cas ou ? CTRL + D etc etc ...
	init_env(&data, envp);
	print_art();// fonction qui affiche le debut de  notre minishell en beaute
	while (1)
	{
		prompt = get_prompt();// recup le prompt
		data.line = readline(prompt);// un input avec l'affichage du prompt
		if (!data.line)
			printf("\n");
		else
		{
			add_history(data.line);
			if (!parsing(&data))
				execution(&data);
			ft_free_no_all(&data);
		}
	}
	return 0;
}
