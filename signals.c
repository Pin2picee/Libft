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

void	ft_sigint(int signal)
{
	(void)signal;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		ft_printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sigquit(int signal)
{
	(void)signal;
}

void	setups_signals(void)
{
	signal(2, ft_sigint);
	signal(3, ft_sigquit);
	signal(SIGTSTP, ft_sigquit);
}
