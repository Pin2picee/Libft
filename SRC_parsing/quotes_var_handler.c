/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by mbetcher          #+#    #+#             */
/*   Updated: 2024/11/20 17:37:47 by abelmoha         ###   ########.fr       */
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
			(*len) = ft_strlen(v_e->value);
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
			(*len)++;
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
		while(str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while(str[i] && str[i] != quote)
			{
				if (ft_strchr("\'\"", str[i]))
				{
					i++;
					break;
				}
				if(quote == '"' && str[i] == '$')
				{
					i++;
					put_var_in_tab(&str[i], tab, data, &j);
				}
				else
					tab[j++] = str[i++];
				if (ft_strchr("\'\"", str[i]))
				{
					i++;
					break;
				}
			}
		}
		if (!ft_strchr("\'\"", str[i]))
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
			tab[i] = ft_clean_tab(tab[i], len, data);
		printf("%s\n", tab[i]);
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

















