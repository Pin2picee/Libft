/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:44 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/19 20:29:54 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "stdio.h"
# include <readline/readline.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
#include <string.h>

struct	s_minishell;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
}				t_env;


typedef struct s_node 
{
	char *hd_end;
	int	fd_in;
	int	fd_out;
	char	*command;
	char	**split_command;
	struct	s_node *next;
	struct s_minishell	*data;
}				t_node;

// chaques noeuds est un entre pipe 
typedef struct	s_minishell
{
	char	*line;
	int		exit_code;
	char	**envp;
	t_env	*var;
	t_node	*start_node;
}				t_minishell;

/* FOR PROMPT*/
char	*get_prompt(void);


/*---PARSING---*/
int		parsing(t_minishell *data);
void	redirections_handler(t_node *node);
int		pre_parsing(char *line); // verif le retour de readline pour voir les erreur qotes et pipes
int		tab_len(char *str, int	*len, t_minishell *data);
void	ft_pass_redirection(char *str, int *i);
void	create_nodes(t_minishell *data);
void	append_nodes(t_minishell *data, int start, int end);
void	add_line_to_node(t_node *node, int start, int end);
void	split_and_clean(t_node *node);
void	quotes_var_handler(char **tab, t_minishell *data);
int		quote_chr(char *str, int i);
void	ft_cpy_file(char *file, char *name_f, int *i, int j);
int		go_redirection(char *name_f, char c, t_node *node, int i);
void	init_j_and_option(int *i, int *option);//gagner des lignes


/*---ENV---*/
void	free_env_vars(t_minishell *data);
t_env	*create_var(const char *key, const char *value);
t_env	*get_env_var(t_env *var_data, const char *key);
void	init_env(t_minishell *data, char **envp);
char	*ft_clean_tab(char *str, int len, t_minishell *data);

/*---EXECUTION---*/
void	ft_env(t_minishell *data);


#endif
