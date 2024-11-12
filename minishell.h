/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:41:44 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/12 13:48:42 by abelmoha         ###   ########.fr       */
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

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_var *next;
}				t_env;


typedef struct s_node 
{
	int	fd_in;
	int	fd_out;
	char	*command;
	char	*s_command;
	struct	s_node *next;
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
int	parsing(t_minishell *data);

int	pre_parsing(char *line); // verif le retour de readline pour voir les erreur qotes et pipes



#endif
