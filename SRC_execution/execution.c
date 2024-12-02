/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:49 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/02 16:25:39 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/**
 * Comment dois fonctionner execution
 * dup2 seulement si plusieyrs noeuds
 * 
*/
bool	check_bultins(t_node *node)
{
	if (!ft_strncmp(node->split[0], "echo", ft_strlen(node->split[0])))
		return (ft_echo(node), true);
	else if (!ft_strncmp(node->split[0], "env", ft_strlen(node->split[0])))
		return (ft_env(node->data), true);
	else if (!ft_strncmp(node->split[0], "exit", ft_strlen(node->split[0])))
		return (ft_exit(node), true);
	else if (!ft_strncmp(node->split[0], "export", ft_strlen(node->split[0])))
		return (ft_export(node, 1), true);
	else if (!ft_strncmp(node->split[0], "cd", ft_strlen(node->split[0])))
		return (ft_cd(), true);
	else if (!ft_strncmp(node->split[0], "pwd", ft_strlen(node->split[0])))
		return (ft_pwd(node->data), true);
	else if (!ft_strncmp(node->split[0], "unset", ft_strlen(node->split[0])))
		return (ft_unset(node), true);
	return (false);
}

/****
 * ft_exec
 * ->access pour voir si il existe
 * si il existe -> alrs -> fork et execve avec redirections
 * appele seulement dans le cas au c'est pas un bultin
*/
void	ft_exec(t_node *node)
{
	
}

void	execution(t_minishell *data)
{
	t_node *current;
	int	*pipe[2];
	int	count_pipe;
	
	count_pipe = 0;
	current = data->start_node;
	while (current->next != NULL)
	{
		count_pipe++;
		current = current->next;
	}
	if (count_pipe != 0)
	{
		pipe = malloc(count_pipe * sizeof(pipe[2]));
	}
	while (data->start_node)
	{
		if (check_bultins(data->start_node) == false)// ce n'est pas un bultins
		{
			ft_exec(data->start_node);//TODO -> c'est elle qui creer les processus fils 
		}
		data->start_node = data->start_node->next;// increment de pipe
	}
}

/**
 * comment se fait la gestion de l execution dans minishell
{
    creer un tableau de pipe int *fd[2]
    verif de si c un builtin ou non
    
    penser a fermer tous les pipes apres utilisation
    bien gerer le retour des commandes que ce soit built in ou non
    
}


*/


