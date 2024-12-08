/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:19:16 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/08 14:59:12 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ajoute 1 au SHLVL a la creation du minishell

void	ft_shlvl(t_minishell *data)
{
	int		i;
	t_env	*current;
	int		tmp;

	current = data->var;
	while (current)
	{
		if (ft_strncmp("SHLVL", current->key, ft_strlen(current->key)) == 0)
		{
			tmp = ft_atoi(current->value) + 1;
			free(current->value);
			current->value = ft_itoa(tmp);
			return ;
		}
		current = current->next;
	}
}

t_env	*create_var(char *key, const char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		printf("Erreur : malloc a échoué\n");
		exit (1);
	}
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	free(key);
	return (new_var);
}

t_env	*get_env_var(t_env *var_data, const char *key)
{
	t_env	*current;

	current = var_data;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// fonction qui init env , setup le signal et affiche GLUANT
void	setup(t_minishell *data, char **envp, int i)
{
	t_env	*current;
	t_env	*new_var;
	char	*equal_sign;

	current = NULL;
	rl_catch_signals = 0;
	data->var = NULL;
	init_data(data);
	while (envp[++i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			new_var = create_var(strndup(envp[i], equal_sign
						- envp[i]), equal_sign + 1);
			if (!data->var)
				data->var = new_var;
			else
				current->next = new_var;
			current = new_var;
		}
	}
	ft_shlvl(data);
	convert_env_to_tab(data);
	print_art();
}
