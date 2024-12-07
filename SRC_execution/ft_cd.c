/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:11:23 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/07 16:54:35 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"	

void ft_cd(t_minishell *data, t_node *current_node)
{
	char	*path;
	int	i;
	char *tmp;
	
	
	path = NULL;
	convert_env_to_tab(data);
	if (!current_node->split[1] ||
		strcmp(current_node->split[1], "~")  == 0)
		path = ft_strdup("/");
	else if (current_node->split[1][0] == '~')
	{
		i = 0;
		 while (data->envp[i] && ft_strncmp(data->envp[i], "HOME=", 5) != 0)
			i++;
		if (data->envp[i] && ft_strncmp(data->envp[i], "HOME=", 5) == 0)
			path = ft_strjoin(data->envp[i] + 5, &current_node->split[1][1]);
	}
	else if (strcmp(current_node->split[1], "-")  == 0)
	{
		i = 0;
		while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD=", 7) != 0)
			i++;
		if (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
			path = ft_strdup((data->envp[i]) + 7);
	}
	else
		path = ft_strdup(current_node->split[1]);
	if (path)
	{
		update_or_add(&data->var, "OLDPWD", ((tmp = getcwd(NULL, 4096))));
		if (chdir(path) < 0)
				perror("\033[34mMinishell \033[0m");
			free(path);
			free(tmp);
		update_or_add(&data->var, "PWD", (tmp = getcwd(NULL, 4096)));
		free(tmp);
	}
	
	return ;
}

/*

Tests :

-
~
/
'\0'
Chemin absolu
Chemin relatif
exit

*/
