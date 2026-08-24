
#include "pipex.h"

void	exit_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
