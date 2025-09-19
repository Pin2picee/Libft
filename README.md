# Minishell

![Minishell Demo](https://github.com/user-attachments/assets/a76d8cd8-05e7-4e84-b5dc-851cdcd4a684)  
*Exemple animé du Minishell en action*

## Description
Minishell est un **interpréteur de commandes minimaliste** inspiré des shells Unix comme `bash`.  
Il est conçu pour comprendre et exécuter des commandes entrées par l’utilisateur, tout en gérant :

- **Les redirections** : `>`, `>>`, `<`  
- **Les pipes** : `|`  
- **Les variables d’environnement**  
- **Les commandes internes** (`cd`, `echo`, `exit`, `export`, etc.)  
- **Le parsing des arguments complexes** avec gestion des quotes et des espaces  

Le projet a pour objectif de **comprendre en profondeur le fonctionnement d’un shell**, la gestion des processus (`fork`, `execve`), et la manipulation des flux d’entrée/sortie en C.

## Installation
1. Clone le dépôt :
```bash
git clone https://github.com/tonpseudo/minishell.git
