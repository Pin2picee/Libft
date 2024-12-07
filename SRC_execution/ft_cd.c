/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:11:23 by nhallou           #+#    #+#             */
/*   Updated: 2024/12/07 02:16:14 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"	

void ft_cd(t_minishell *data, t_node *current_node)
{
	char	*path;
	int	i;
    
    i = 0;
	path = NULL;
    if (!current_node->split[1] ||
        strcmp(current_node->split[1], "~")  == 0)
    {
        while (data->envp[i] && ft_strncmp(data->envp[i], "HOME=", 5) != 0)
            i++;
        if (data->envp[i] && ft_strncmp(data->envp[i], "HOME=", 5) == 0)
        	path = ft_strdup(data->envp[i] + 5);
    }
    else if (strcmp(current_node->split[1], "-")  == 0)
    {
        while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD=", 7) != 0)
            i++;
        if (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
        	path = ft_strdup((data->envp[i]) + 7);
    }
    else
        path = ft_strdup(current_node->split[1]);
	if (path)
	{
        update_or_add(&data->var, "OLDPWD", (getcwd(NULL, 4096)));
		if (chdir(path) < 0)
            perror("\033[34mMinishell \033[0m");
        free(path);
    }
    update_or_add(&data->var, "PWD", (getcwd(NULL, 4096)));
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
