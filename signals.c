
#include "minishell.h"

t_minishell *data;

void	control_c_and_d(int signum, sig_info_t *info, void *context)
{

}


void	setup_signals(t_minishell *pointeur_data)
{
	struct sigaction sa;

	data = pointeur_data;
	sa.sa_flags = SA_SIGINFO;// flag pour que le system envoie les bonne info -> pour la fonction avance
	sa.sa_sigaction = control_c_and_d;// application d'un gestionnaire avance->(sa_sigaction) au lieu de (sa_handler)
	sigemptyset(&sa.sa_mask); // pas de fil d'attente donc tout les signaux peuvent etre intercepte a tout moment
	sigaction(SIGINT, &sa, NULL);
	sigaction()
	
	
}


/**
 * comment gerer control + c et control + v
 * pointeur global
 * dans la fonction setup_signal je defini le pointeur global pour ma data
 * si ctrl + c je dois ft_reset mais avec signal normal je ne peux pas donner un pointeur vers ma structure donne sigaction
 * je creer ma structure je definie le flag SA_SIGINFO pour mettre a true ->fonction perso
 * je defini ma fonction sigaction qui sera appele pour chaque signal
 * puis je sigemptyset je vide le masque de signal pour pouvoir tous les geres a nimporte
 *  quelle moment -> je les debloque=> je ne les faits pas attendre les un et les autres si ctrl+c en cours je peux quand meme ctrl+d par exemple
 * je defini les signal
 * et fait les fonctions 
 */