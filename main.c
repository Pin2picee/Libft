/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/19 11:55:03 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	t_minishell	*data;
	
	(void)argv;
	if (argc != 1)
		return (perror("Error\n"), 1);
	
	init_env(&data, envp);
	//petit flag;
	while (1)
	{
		prompt = get_prompt();
		data->line = readline(prompt);
		
		add_history(data->line);
		if (!parsing(data))
			execution(data);
		//fonction_qui free : TODO/
	}
    return 0;
}
/*salut test mago*/


