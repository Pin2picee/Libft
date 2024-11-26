#include "../minishell.h"

int exit_builtin()
{
    
}

Exit ne marche que quand il  est tout seul car cest un builtin. 
Quand il y a des pipes, bash cree des processus 
indistinctement de si ce sont des builtins ou non.

