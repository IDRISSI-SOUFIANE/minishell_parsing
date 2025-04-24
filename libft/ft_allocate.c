#include "../include/minishell.h"


char	*ft_allocate(char **res, int len)
{
	*res = malloc(len + 1);
	if (!(*res))
		return (NULL);
	return (*res);
}