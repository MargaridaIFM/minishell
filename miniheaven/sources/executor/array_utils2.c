#include "../includes/minishell.h"

/**
 * @brief Counts an array and returns the number of elements
 * @param char **arr
 * @return int
 */
int	count_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
