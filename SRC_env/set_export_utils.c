#include "../minishell.h"

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Trie a bulles
void	bubble_sort(char **export)
{
	int		swapped;
	size_t	n;
	size_t	i;

	n = 0;
	while (export[n])
		n++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < n - 1)
		{
			if (strcmp(export[i], export[i + 1]) > 0)
			{
				swap_strings(&export[i], &export[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}
