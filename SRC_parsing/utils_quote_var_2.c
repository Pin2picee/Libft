/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote_var_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:52:26 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 21:17:55 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_num(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	tab_len(char *str, int	*len, t_minishell *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = chr_quotes_or_d(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar_handler(str, len, data, &i);
			continue ;
		}
		if (str[i] == '\'' || str[i] == '"')
			i += quotes_len(&str[i], str[i], data, len);
		else if (flag == 1)
		{
			i++;
			(*len)++;
		}
		else
			i++;
	}
	return (i);
}

int	put_var_in_tab(char *str, char *tab, t_minishell *data, int *j)
{
	int		i;
	t_env	*v_e;

	v_e = data->var;
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0 && str[0])
		return (1);
	while (v_e)
	{
		if (!ft_strncmp(v_e->key, str, i) && ft_strlen(v_e->key) == i)
		{
			ft_strlcat(tab, v_e->value, *j + ft_strlen(v_e->value) + 1);
			*j = ft_strlen(tab);
			return (i);
		}
		else
			v_e = v_e->next;
	}
	return (i);
}
