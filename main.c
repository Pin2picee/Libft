/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/19 20:33:55 by abelmoha         ###   ########.fr       */
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
<<<<<<< HEAD
	setup_signals();
=======
	
>>>>>>> 82f3633f5fc49236e9829d3d76a906e601979f79
	init_env(&data, envp);
	//petit flag;
	while (1)
	{
		prompt = get_prompt();
		data.line = readline(prompt);
		if (!data.line)
		{
			printf("exit\n");
			break;
		}
		add_history(data.line);
		if (!parsing(&data))
			execution(&data);
		ft_free_all(&data);
	}
	ft_free_all(&data);
	return 0;
}
/*salut test mago*/


