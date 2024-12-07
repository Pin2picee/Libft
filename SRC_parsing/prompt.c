/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:45:45 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 17:42:48 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	ft_host_pwd(char **prompt, int *i)
{
	char	pwd[4096];
	int		j;
	char	hostname[500];
	int		fd_hostname;

	j = 0;
	fd_hostname = open("/etc/hostname", O_RDONLY);
	read(fd_hostname, hostname, 200);
	close("/etc/hostname");
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
	prompt = ft_calloc(4096, sizeof(char));
	user = getenv("USER");
	i += ft_strlcpy(prompt, user, 100);
	prompt[i++] = '@';
	ft_host_pwd(&prompt, &i);
	prompt_clean = ft_calloc(ft_strlen(prompt) + 3, sizeof(char));
	ft_strlcpy(prompt_clean, prompt, ft_strlen(prompt) + 1);
	free(prompt);
	return (prompt_clean[i++] = '$', prompt_clean[i] = ' ', prompt_clean);
}*/

void	ft_host_pwd(char **prompt, int *i)
{
	char	pwd[4096];
	char	hostname[500];
	int		fd_hostname;
	ssize_t	bytes_read;
	int		j;

	j = 0;
	fd_hostname = open("/etc/hostname", O_RDONLY);
	if (fd_hostname < 0)
		return ;
	bytes_read = read(fd_hostname, hostname, sizeof(hostname) - 1);
	close(fd_hostname);
	if (bytes_read <= 0)
		return ;
	hostname[bytes_read] = '\0';
	while (hostname[j] != '.' && hostname[j])
		(*prompt)[(*i)++] = hostname[j++];
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return ;
	(*prompt)[(*i)++] = ':';
	(*prompt)[(*i)++] = '~';
	j = 0;
	while (pwd[j] && (*i) < 4095)
		(*prompt)[(*i)++] = pwd[j++];
}

char	*get_prompt(void)
{
	int		i;
	char	*user;
	char	*prompt;
	char	*prompt_clean;

	i = 0;
	prompt = ft_calloc(4096, sizeof(char));
	if (!prompt)
		return (NULL);
	user = getenv("USER");
	if (user)
		i += ft_strlcpy(prompt, user, 100);
	prompt[i++] = '@';
	ft_host_pwd(&prompt, &i);
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	prompt_clean = ft_strdup(prompt);
	free(prompt);
	return (prompt_clean);
}


void	ft_tkt(t_node *node)
{
	if (!node->hd)
	{
		node->hd = ft_calloc(1, 1);
	}
}