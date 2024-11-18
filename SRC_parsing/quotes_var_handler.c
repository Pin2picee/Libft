/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/11/18 13:27:34 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chr_quotes(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '"')
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
	while(v_e) 
	{
		if (!ft_strncmp(v_e->key, str, i))
		{
		*len = ft_strlen(v_e->value);
			return(i);
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
		}
		else
			i++;
	}
	return (i + 1);
}

int	tab_len(char *str, int	*len, t_minishell *data)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = chr_quotes(str);
	while(str[i])
	{	
		if(str[i] == '$')
		{
			i++;
			var_len(&str[i], data, len);
		}
		if(str[i] == '\'' || str[i] == '"')
		{
			i += quotes_len(&str[i], str[i], data, len);
		}
		else if(flag == 1)
		{
			i++;
			*len++;
		}
		else
			i++;
	}
	return (i);
}

void	put_var_in_tab(char *str, char *tab, t_minishell *data, int *main_i)
{
	int	i;
	t_env	*v_e;
	
	v_e = data->var;
	i = 0;
	while(str[i] && (isalnum(str[i]) || str[i] == '_'))
		i++;
	while(v_e) 
	{
		if (!ft_strncmp(v_e->key, str, i + 1))
		{
			ft_strlcat(tab, v_e->value, *main_i);
			*main_i += ft_strlen(v_e->value);
			return ;
		}
		else
			v_e = v_e->next;
	}
}

char	*ft_clean_tab(char *str, int len, t_minishell *data)
{
	char	*tab;
	int	i;
	int	j;
	char	quote;
	
	i = 0;
	j = 0;
	tab = malloc(len + 1);
	if (!tab)
		return (NULL);
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while(str[i] && str[i] != quote)
			{
				if(quote == '"' && str[i] == '$')
				{
					i++;
					put_var_in_tab(&str[i], tab, data, &j);
				}
				else
					tab[j++] = str[i++];
			}
		}
		else
			tab[j++] = str[i++];
	}
	free(str);
	tab[j] = '\0';
	return (tab);
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
		printf("%i\n", len);
		if (len !=0)
			tab[i] = ft_clean_tab(&tab[i][0], len, data);
		printf("%s\n", tab[i]);
		i++;
		
	}
}

int main(int ac, char **av)
{
    (void)ac;
    t_minishell data;
    // Initialisation d'un tableau d'exemple pour tester quotes_var_handler
    char *example_tab[] = {
        "\'t$est\'",
        "ex\"a\"mple2",
        "sample3",
        NULL
    };
	
    // Appel de la fonction pour tester
    quotes_var_handler(example_tab, &data);

    return 0;
}



















