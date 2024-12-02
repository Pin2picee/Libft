/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/12/02 16:38:10 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	putnbr_in_tab(t_minishell *data, char *tab)
{
	char	*nb;
	int		len;
	
	nb = ft_itoa(data->exit_code);
	ft_strlcpy(tab, nb, 3);
	len = ft_strlen(nb);
	free(nb);
	return(len);
}
int	chr_quotes_or_d(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '"' || str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
int	var_len(char *str, t_minishell *data, int *len)
{
	int	i;
	t_env	*v_e;
	
	v_e = data->var;
	i = 0;
	while(str[i] && (isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0 && str[0])
		return (1);
	while(v_e) 
	{
		if (!ft_strncmp(v_e->key, str, ft_strlen(v_e->key)) && ft_strlen(v_e->key) == i)
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
		if(quote == '"' && str[i] == '$')
		{
			i++;
			i += var_len(&str[i], data, len);
			continue;
		}
		else
		{
			(*len)++;
			i++;
		}
	}
	return (i + 1);
}

void	dollar_handler(char *str, int *len, t_minishell * data, int *i)
{
	
	(*i)++;
	if (str[*i] == '?')
	{
		*(len) += 3;
		(*i)++;
	}
	else
		(*i) += var_len(&str[*i], data, len);
}

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

char	*ft_clean_tab(char *str, int len, t_minishell *data)
{
	char	*tab;
	int	i;
	int	j;
	char	quote;
	
	i = 0;
	j = 0;
	tab = ft_calloc(len + 2, sizeof(char));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		while(str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				i++;
				j += putnbr_in_tab(data, &tab[j]);
			}
			i += put_var_in_tab(&str[i], tab, data, &j);
		}
		while(str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while(str[i] && str[i] != quote)
			{
				if (quote == str[i])
				{
					i++;
					break;
				}
				while(quote == '"' && str[i] == '$')
				{
					i++;
					i += put_var_in_tab(&str[i], tab, data, &j);
				}
				if (!(quote == '"' && str[i] == '$'))
					tab[j++] = str[i++];
				if (quote == str[i])
				{
					i++;
					break;
				}
			}
		}
		if (!ft_strchr("\'\"", str[i]))
				tab[j++] = str[i++];
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
	while(tab[i])
	{
		len = 0;
		tab_len(&tab[i][0], &len, data);
		if (len ==  0 && ft_strchr(tab[i], '$'))
			tab[i] = ft_clean_tab(tab[i], len, data);
		else if (len != 0)
			tab[i] = ft_clean_tab(tab[i], len, data);
		i++;
	}
}







