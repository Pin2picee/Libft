/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/07 22:34:48 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_var(t_quotes *q)
{
	if (q->str[q->i] == '?')
	{
		q->i++;
		putnbr_in_tab(q->data, &q->tab[q->j]);
		q->j = ft_strlen(q->tab);
		return (1);
	}
	q->i += put_var_in_tab(&q->str[q->i], q->tab, q->data, &q->j);
	return (0);
}

void	handle_quotes(t_quotes *q)
{
	char	quote;

	quote = q->str[q->i++];
	while (q->str[q->i] && q->str[q->i] != quote)
	{
		if (quote == '"' && q->str[q->i] == '$')
		{
			q->i++;
			handle_var(q);
		}
		else
			q->tab[q->j++] = q->str[q->i++];
	}
	if (q->str[q->i] == quote)
		q->i++;
}

char	*ft_clean_tab(char *str, int len, t_minishell *data)
{
	char		*tab;
	t_quotes	q;

	tab = ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (NULL);
	q.tab = tab;
	q.str = str;
	q.data = data;
	q.i = 0;
	q.j = 0;
	while (q.str[q.i])
	{
		if (q.str[q.i] == '$')
		{
			q.i++;
			handle_var(&q);
		}
		else if (q.str[q.i] == '\'' || q.str[q.i] == '"')
			handle_quotes(&q);
		else if (q.str[q.i])
			q.tab[q.j++] = q.str[q.i++];
	}
	return (free(str), tab);
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
