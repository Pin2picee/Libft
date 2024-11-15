/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_var_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:28:33 by abelmoha          #+#    #+#             */
/*   Updated: 2024/11/13 19:49:12 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

ce que je recois : 
{
	un tableau splite nettoye des redirections et qui contient tjrs les "" et $
}
ce que je dois retourner
{
	un **tab nettoye de ses quotes et ou les $ ont ete attribues si existante.
}

comment m y prendre
{
	rentrer dans une boucle tant qu il y a des tabs
	{
		si il y a une quote
		{
			calculer la len de mon tab mallocquer
			{
				comment calculer la len
				{
					si j ai une quote '"', 
					{
						activer un flag d_quote et incrementer ma len;
						si je tombe sur $
						{
							rentrer dans ma fonction env_var_chr
							{
								va prendre la var et la comparer a la cle de toutes les VE
								{
									pour eviter de mallocquer je vais faire un strncmp qui 
									recupere la va et ne compare que les key avec sa len
									comment recuperer la VE
									{
										incrementer tant que tab[i] == caracteres alphanumeriques 
										ou '_'.
									}	
								}
								mtn que j ai ma VA, je recupere sa len et je continue; 
							}
						}
					}
					si j ai une quote '\''
					{
						simplement implementer la len en ignorant les '\'';
					}
				}
			}
		}
		si len est != 0, alors on a trouve des quotes et on malloc un tableau a la taille de
		cette len
		 les cas que je dois gerer
		{
			- "$USER""b" dans un meme tableau
			comment m y prendre
			{
				utiliser un flag d_quote pour savoir si je gere les $ ou non.
				refaire le meme proceder que dans le calcul de la len pour recuperer le nom
				de la VA
				et ecrire les caracteres dans mon tableau 
			}
		}
		
	}
	free lancien tableau contenu dans le **tab si modification il y a eu.

	}
}

echo slut"'"