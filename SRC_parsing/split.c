/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:02 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 18:39:13 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_word(char *command, int i, int count, bool flag)
{
	if (!command[i] || !command)
		return (i);
	while (i < ft_strlen(command) && command[i])
	{
		while (i < ft_strlen(command) && command[i]
			&& (command[i] == ' ' || command[i] == '\t'))
		{
			flag = 1;
			i++;
		}
		while (i < ft_strlen(command) && command[i]
			&& command[i] != ' ' && command[i] != '\t')
		{
			if (flag == 1)
			{
				count++;
				flag = 0;
			}
			if (command[i] && ft_strchr("\'\"", command[i]))
				i = quote_chr(command, i) + 1;
			else
				i++;
		}
	}
	return (count);
}

int	split_minishell(t_node *node, char *sep, int i, int j)
{
	int	t;

	t = 0;
	node->split = ft_calloc((count_word(node->command, 0, 0, true) + 2),
			sizeof(char *));
	if (node->split == NULL)
		return (printf("malloc error split"), 1);
	while (node->command[i] && ft_strchr(sep, node->command[i]))
		i++;
	j = i;
	while (node->command[j])
	{
		while (node->command[j] && !ft_strchr(sep, node->command[j]))
		{
			if (node->command[j] && ft_strchr("\'\"", node->command[j]))
				j = quote_chr(node->command, j) + 1;
			else
				j++;
		}
		node->split[t++] = ft_strldup(node->command + i, j - i);
		while (node->command[j] && ft_strchr(sep, node->command[j]))
			j++;
		i = j;
	}
	return (0);
}

void	split_and_clean(t_node *node)
{
	redirections_handler(node);
	if (count_word(node->command, 0, 0, true))
		split_minishell(node, " \t", 0, 0);
	else
		node->split = NULL;
	if (node->split)
		quotes_var_handler(node->split, node->data);
}
