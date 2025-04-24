#include "../include/minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	cc;

	s = (unsigned char *)b;
	cc = (unsigned char)c;
	while (len--)
	{
		s[len] = cc;
	}
	return (b);
}