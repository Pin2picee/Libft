/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/11/27 13:01:12 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	tab_len(char *str, int	*len, t_minishell *data)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = chr_quotes_or_d(str);
	while(str[i])
	{	
		//if()
		if(str[i] == '$')
		{
			i++;
			i += var_len(&str[i], data, len);
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
		printf("%d", len);
		if (len ==  0 && ft_strchr(tab[i], '$'))
			tab[i] = ft_clean_tab(tab[i], len, data);
		else if (len != 0)
			tab[i] = ft_clean_tab(tab[i], len, data);
		i++;
	}
}
/*
int main(int ac, char **av)
{
    (void)ac;
    t_minishell data;

    // Initialisation dynamique d'un tableau de chaînes de caractères malocées
    char **example_tab = malloc(4 * sizeof(char *));
    if (!example_tab)
    {
        perror("malloc failed");
        return 1;
    }

    example_tab[0] = malloc(strlen("\"test\"\"'s'\"") + 1);
    if (example_tab[0])
        strcpy(example_tab[0], "\"test\"\"\"'s'");
    example_tab[1] = malloc(strlen("ex\"a\"mple2") + 1);
    if (example_tab[1])
        strcpy(example_tab[1], "ex\"a\"mple2");
    example_tab[2] = malloc(strlen("sample3") + 1);
    if (example_tab[2])
        strcpy(example_tab[2], "sample3");
    example_tab[3] = NULL; // Terminate the array with NULL

    // Appel de la fonction pour tester
    quotes_var_handler(example_tab, &data);

    // Libération de la mémoire allouée
    for (int i = 0; example_tab[i] != NULL; i++)
        free(example_tab[i]);
    free(example_tab);
    return 0;
}
*/






/*
rajouter la gestion du $? cela se fera dans var_len et put_var_in_tab
{
	comment le rajouter ?
	si tab[i] = $ et que tab[i + 1] = ?, alors i += 2; 
	else 
	la len max est 3;
	aller chercher data->exit_code, faire un putnbr_in_tab avec strlcat;
}

*/
//verifier pq les v_e colles marchent une fois sur deux









