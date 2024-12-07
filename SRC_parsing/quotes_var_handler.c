/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/07 19:32:14 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_var(char *str, char *tab, t_minishell *data, int *i, int *j)
{
	if (str[*i] == '?')
	{
		(*i)++;
		*j += putnbr_in_tab(data, &tab[*j]);
		return (1);
	}
	*i += put_var_in_tab(&str[*i], tab, data, j);
	return (0);
}

void	handle_quotes(char *str, char *tab, t_minishell *data, int *i, int *j)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && str[*i] == '$')
		{
			(*i)++;
			handle_var(str, tab, data, i, j);
			*i += ft_count_num(data->exit_code);
		}
		else
			tab[(*j)++] = str[(*i)++];
	}
	if (str[*i] == quote)
		(*i)++;
}

char	*ft_clean_tab(char *str, int len, t_minishell *data)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			handle_var(str, tab, data, &i, &j);
		}
		else if (str[i] == '\'' || str[i] == '"')
			handle_quotes(str, tab, data, &i, &j);
		else if (str[i])
			tab[j++] = str[i++];
	}
	free(str);
	return (tab);
}

void	quotes_var_handler(char **tab, t_minishell *data)
{
	char	**clean_tab;
	int		i;
	int		len;
	char	quote;

	i = 0;
	while (tab[i])
	{
		len = 0;
		tab_len(&tab[i][0], &len, data);
		if (ft_strncmp(tab[i], "\"\"", 2) == 0
			|| ft_strncmp(tab[i], "''", 2) == 0)
		{
			free(tab[i]);
			tab[i] = ft_calloc(1, 1);
		}
		else if (len == 0 && (ft_strchr(tab[i], '$')
				|| ft_strchr(tab[i], '\'') || ft_strchr(tab[i], '"')))
			tab[i] = ft_clean_tab(tab[i], len, data);
		else if (len != 0)
			tab[i] = ft_clean_tab(tab[i], len, data);
		i++;
	}
}
