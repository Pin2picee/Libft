/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/06 17:04:45 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tab_len(char *str, int	*len, t_minishell *data)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = chr_quotes_or_d(str);
	while(str[i])
	{	
		if(str[i] == '$')
		{
			dollar_handler(str, len, data, &i);
				continue;
		}
		if(str[i] == '\'' || str[i] == '"')
			i += quotes_len(&str[i], str[i], data, len);
		else if(flag == 1)
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
	int	i;
	t_env	*v_e;
	
	v_e = data->var;
	i = 0;
	//if (str[i] == '?')
	//	putnbr_in_tab(data, tab	);
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0 && str[0])
		return (1);
	while(v_e) 
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
	data->exit_code = 1547;
	while(tab[i])
	{
		len = 0;
		tab_len(&tab[i][0], &len, data);
		if (ft_strncmp(tab[i], "\"\"", 2) == 0 || ft_strncmp(tab[i], "''", 2) == 0)
		{
			free(tab[i]);
			tab[i] = ft_calloc(1, 1);
		}
		else if (len ==  0 && (ft_strchr(tab[i], '$') || ft_strchr(tab[i], '\'') || ft_strchr(tab[i], '"')))
			tab[i] = ft_clean_tab(tab[i], len, data);
		else if (len != 0)
			tab[i] = ft_clean_tab(tab[i], len, data);
		i++;
	}
}







