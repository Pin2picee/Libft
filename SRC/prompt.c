/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:45:45 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/11 12:36:23 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_host_pwd(char **prompt, int *i)
{
	char	pwd[4096];
	int		j;
	char	hostname[500];
	int		fd_hostname;

	j = 0;
	fd_hostname = open("/etc/hostname", O_RDONLY);
	read(fd_hostname, hostname, 200);
	while (hostname[j] != '.' && hostname[j])
		(*prompt)[(*i)++] = hostname[j++];
	j = 0;
	getcwd(pwd, sizeof(pwd));
	(*prompt)[(*i)++] = ':';
	(*prompt)[(*i)++] = '~';
	while ((*i) < 249 && pwd[j])
	{
		(*prompt)[*i] = pwd[j];
		j++;
		(*i)++;
	}
	return ;
}

char	*get_prompt(void)
{
	int		i;
	int		j;
	char	*user;
	char	*prompt;
	char	*prompt_clean;

	i = 0;
	j = 0;
	prompt = malloc(4096);
	user = getenv("USER");
	i += ft_strlcpy(prompt, user, 100);
	prompt[i++] = '@';
	ft_host_pwd(&prompt, &i);
	prompt_clean = ft_calloc(ft_strlen(prompt) + 2, sizeof(char));
	ft_strlcpy(prompt_clean, prompt, ft_strlen(prompt) + 1);
	free(prompt);
	return (prompt_clean[i] = '$', prompt_clean);
}
