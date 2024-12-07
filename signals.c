/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbetcher <mbetcher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:35:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/12/07 17:30:03 by mbetcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"



/*
    Gestion pour SIGINT (ctrl+c)
*/
void    ft_sigint(int signal)
{                                           // (-1) -> Indique qu'on attend n'importe procss fils)  
    (void)signal;                           // (NULL) -> Pas de stockage des information de status
    if (waitpid(-1, NULL, WNOHANG) == -1)   // (WNOHANG) -> Pas bloquer l'appel si aucun procss fils n'a terminé
    {
        ft_printf("^C\n");
        rl_on_new_line();               // Prepare readline pour une nouvelle ligne
        rl_replace_line("", 0);         // clean la ligne actuelle
        rl_redisplay();                 // Reaffiche le prompt
    }
}
/*
    Gestion pour SIGQUIT (ctrl+\)
*/
void    ft_sigquit(int signal)
{   
    (void)signal;
}


void    setups_signals(void)
{
    signal(2, ft_sigint);
    signal(3, ft_sigquit);
    signal(SIGTSTP, ft_sigquit);
}
