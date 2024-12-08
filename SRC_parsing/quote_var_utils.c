/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_var_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:48:57 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/08 15:04:41 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	putnbr_in_tab(t_minishell *data, char *tab)
{
	char	*nb;
	int		len;

	nb = ft_itoa(data->exit_code);
	ft_strlcpy(tab, nb, 4);
	len = ft_strlen(nb);
	free(nb);
	return (len);
}

int	chr_quotes_or_d(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	var_len(char *str, t_minishell *data, int *len)
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
		if (!ft_strncmp(v_e->key, str, ft_strlen(v_e->key))
			&& ft_strlen(v_e->key) == i)
		{
			(*len) += ft_strlen(v_e->value);
			return (i);
		}
		else
			v_e = v_e->next;
	}
	return (i);
}

int	quotes_len(char *str, char quote, t_minishell *data, int *len)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
	{
		if (quote == '"' && str[i] == '$')
		{
			dollar_handler(str, len, data, &i);
			continue ;
		}
		else
		{
			(*len)++;
			i++;
		}
	}
	return (i + 1);
}

void	dollar_handler(char *str, int *len, t_minishell *data, int *i)
{
	(*i)++;
	if (str[*i] == '?')
	{
		*(len) += ft_count_num(data->exit_code);
		(*i)++;
	}
	else
		(*i) += var_len(&str[*i], data, len);
}
