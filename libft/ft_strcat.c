#include "../include/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int des_len;
	int	i;

	des_len = ft_strlen(src);
	i = 0;
	while (src[i])
	{
		dest[des_len + i] = src[i];
		i++;
	}
	dest[des_len + i] = '\0';
	return (dest);
}
