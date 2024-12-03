/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:44 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/02 16:42:03 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h> // Nécessaire pour add_history
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

extern int	signal_handler;

struct	s_minishell;

typedef enum es_bin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_e_bin;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		is_export_only;	// (0 -> key=value) et (1 -> key) 
	struct s_env *next;
}				t_env;


typedef struct s_nodes
{
	char *hd;// Adil la modif ancien -> hd_end
	int	fd_in;
	int	fd_out;
	int	pos; // ADDED
	char	*cmd_path; // ADDED
	t_e_bin	cmd_type;	// ADDED
	char	*command;
	char	**split;
	struct	s_nodes *next;
	struct s_minishell	*data;
}				t_node;

// chaques noeuds est un entre pipe 
typedef struct	s_minishell
{
	int		node_nbr; // ADDED
	int		(*pipe_tab)[2]; // ADDED
	t_node	*current_node; // ADDED
	pid_t   pid; // ADDED
	int	status; // ADDED
	int	fd_stdin; //ADDED
	int fd_stdout; // ADDED
	t_node  *current_node; // ADDED
	char	*line;
	int		exit_code;
	char	**envp;
	char 	**export;
	t_env	*var;
	t_node	*start_node;
	char	*prompt;
}				t_minishell;

/* FOR PROMPT*/
char	*get_prompt(void);


/*---PARSING---*/
void	create_nodes(t_minishell *data);
int		parsing(t_minishell *data);
int		quote_chr(char *str, int i);
int		pre_parsing(char *line); // verif le retour de readline pour voir les erreur qotes et pipes
int		parsing(t_minishell *data);
void	redirections_handler(t_node *node);
int		pre_parsing(char *line); // verif le retour de readline pour voir les erreur qotes et pipes
int		tab_len(char *str, int	*len, t_minishell *data);
void	ft_pass_redirection(char *str, int *i);
void	create_nodes(t_minishell *data);
void	append_nodes(t_minishell *data, int start, int end, char *tab);
void	add_line_to_node(t_node *node, int start, int end, char *line);
void	split_and_clean(t_node *node);
void	quotes_var_handler(char **tab, t_minishell *data);
int		quote_chr(char *str, int i);
void	ft_cpy_file(char *file, char *name_f, int *i, int j);
int		go_redirection(char *name_f, char c, t_node *node, int i);
void	init_j_and_option(int *i, int *option);//gagner des lignes
void	ft_here_doc(char *final_word, t_node *node);
int		redirections_syntax(char *line);
int		split_minishell(t_node *node, char *sep, int i, int	j);
char	*ft_clean_tab(char *str, int len, t_minishell *data);
void	init_data(t_minishell *data);
void	init_node(t_node *node);


/*- - - SRC_ENV - - -*/
//-> dbug_env.c
//void	display_env(t_minishell *data);
//void	print_export(t_minishell *data);
//void	print_envp(t_minishell *data);
//-> env_utils.c
void	free_env_vars(t_minishell *data);
void	free_tab(char **export);
//-> set_env.c
t_env	*create_var(char *key, const char *value);
t_env	*get_env_var(t_env *var_data, const char *key);
void	setup(t_minishell *data, char **envp);


//-> set_export_utils.c
void	swap_strings(char **a, char **b);
void	bubble_sort(char **export);
//-> set_export_tab.c
size_t	count_env_vars(t_env *env_list);
char	**allocate_env_tab(size_t count);
void	fill_env_tab(char **tab, t_env *env_list, size_t count);
void	convert_env_to_tab(t_minishell *data);
//-> set_export.c								
int		parse_name_value(const char *arg, char **name, char **value);
int		update_env_var(t_env *env_list, const char *name, const char *value);
void	add_env_var(t_env **env_list, const char *name, const char *value);
void	update_or_add(t_env **env_list, const char *name, const char *value);


/*- - - SRC_EXECUTION - - -*/
//-> ft_env
void	ft_env(t_minishell *data);
//-> ft_export
void	ft_printf_export(t_minishell *data);
void	ft_SHLVL(t_minishell *data);

//-> ft_unset
void 	unset_env_var(t_env **env_list, const char *name);
void 	ft_unset(t_node *node);


/* - - - SIGNALS - - - */
void    setups_signals(void);


/*---BULTINS---*/
void	ft_echo(t_node *node);
void	ft_env(t_minishell *data);
void    ft_exit(t_node *node);
void	ft_export(t_node *node, int i);
void	ft_pwd(t_minishell *data);
void 	ft_unset(t_node *node);


//void	execution(t_minishell *data);

/*---affichage---*/
void 	print_art(void);

/*------FREE-----------*/
void	ft_reset(t_minishell *data);// reset dans la boucle juste ma ligne et les noeuds
void	free_all(t_minishell *data);// reset tout pour CTRL + D et exit // suppr env et tout ca

/*------A TRIER-----------*/
int		ft_exec(t_minishell *data);
int		check_builtin(t_node *node, char *cmd);
void	check_execve(t_minishell *data, char *cmd, t_node *current);
void 	manage_pipe_parent(t_minishell *data, int param);
void	manage_pipe_fork(t_minishell *data, t_node **node);
void    create_fork(t_minishell *data, t_node **node, pid_t *pid);
void    close_pipe_fork(t_minishell *data, t_node *node, int param, int i);

#endif
