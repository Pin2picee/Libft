/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:08:31 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/08 15:06:06 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_fd(char *filename, int option, t_node *node, int len)
{
	char	*error;

	if (!*filename)
		return ;
	tab_len(filename, &len, node->data);
	if (len != 0)
		filename = ft_clean_tab(filename, len, node->data);
	if (option == 1)
		node->fd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (option == 2)
		node->fd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (option == 3)
		node->fd_in = open(filename, O_RDONLY);
	if (node->fd_in < 0 || node->fd_out < 0)
	{
		error = ft_strjoin("Minishell: ", filename);
		perror(error);
		free(error);
		free(filename);
		node->data->exit_code = 1;
		return ;
	}
	if (option == 4)
		ft_here_doc(filename, node, NULL, NULL);
	free(filename);
}

int	go_redirection(char *n_f, char c, t_node *node, int i)
{
	char	file[FILENAME_MAX];
	int		option;
	int		j;

	init_j_and_option(&j, &option);
	if (c == '<' && !ft_strchr("<>", n_f[i]))
		option = 3;
	if (n_f[i] == '>' && n_f[i] == c)
		option = 2;
	if (n_f[i] == '<' && n_f[i] == c)
		option = 4;
	if (((n_f[i + 1] == '>' || n_f[i + 1] == '<') && ft_strchr("><", n_f[i]))
		|| (n_f[i] != c && ft_strchr("><", n_f[i])))
		return (ft_putstr_fd("Redirections syntax error !\n", 2), -42);
	if (n_f[i] == ' ' || n_f[i] == '\t')
	{
		while (n_f[i] == ' ' || n_f[i] == '\t')
			i++;
		if (ft_strchr("><", n_f[i]))
			return (ft_putstr_fd("Redirections syntax error !\n", 2), -42);
	}
	if (n_f[i] && n_f[i + 1] && ft_strchr("\'\"", n_f[i + 1]))
		i++;
	return (ft_cpy_file(file, n_f, &i, j),
		do_fd(ft_strdup(file), option, node, 0), i + 1);
}

void	clean_commands(t_node *node, int i, int j)
{
	char	*str;

	str = ft_calloc((int)ft_strlen(node->command) + 2, sizeof(char));
	while (i < ft_strlen(node->command) && node->command[i])
	{
		while (node->command[i] && ft_strchr("<>", node->command[i]))
			ft_pass_redirection(node->command, &i);
		if (node->command[i] == '"' || node->command[i] == '\'')
		{
			if (node->command[i + 1] == node->command[i])
				i = i + 2;
			else
			{
				ft_strlcpy(str + j, node->command + i,
					quote_chr(node->command, i) - i + 2);
				j = ft_strlen(str);
				i = quote_chr(node->command, i) + 1;
			}
		}
		else
			str[j++] = node->command[i++];
	}
	free(node->command);
	node->command = str;
}

void	redirections_handler(t_node *node)
{
	int	i;
	int	check;

	i = 0;
	while (i < ft_strlen(node->command) && node->command[i])
	{
		while (i < ft_strlen(node->command)
			&& node->command[i] == '"' || node->command[i] == '\'')
			i = quote_chr(node->command, i) + 1;
		while (i < ft_strlen(node->command)
			&& (node->command[i] == '>'
				|| node->command[i] == '<') && node->command[i])
		{
			check = go_redirection(node->command + i + 1,
					node->command[i], node, 0);
			if (check == (-42))
				return ;
			i += check;
		}
		i++;
	}
	if (node->command)
		clean_commands(node, 0, 0);
	return ;
}
