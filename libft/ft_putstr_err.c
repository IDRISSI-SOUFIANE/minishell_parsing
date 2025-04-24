/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:30:47 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/01 23:48:14 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
int	ft_specifcChar(t_keyword type)
{
	return (type == WRITE_OUT || type == APPEND || type == READ_IN || HERDOC);
}

void	ft_putstr_err(char *error, char *value, t_keyword type, int count)
{
	int j;

	j = 0;
	while (value[j])
		j++;
	if ((j == 1 || j == 2) && (ft_spchar(type)))
	    printf("%s \`newline\'", error);
	else if (j == 3 && ft_spchar(type) && type == APPEND)
	    printf("%s \`>'", error);
	else if (j > 3 && ft_spchar(type) && type == APPEND)
	    printf("%s \`>>\'", error);
	else if (j == 3 && ft_spchar(type) && type == HERDOC)
	    printf("%s \`newline\'", error);
	else if (j == 4 && ft_spchar(type) && type == HERDOC)
	    printf("%s \`<\'", error);
	else if (j == 5 && ft_spchar(type) && type == HERDOC)
	    printf("%s \`<<\'", error);
	else if (j > 5 && ft_spchar(type) && type == HERDOC)
	    printf("%s \`<<<\'", error);

	//khasni nhadli ila kan 3andi |>> <<| pipes special case

	else if (j == 1 && value[0] == '|')
	    printf("%s \`%s\'", error, value);
	// if (value == "|" && i == 1)
	//     printf("%s \`%s\'", error, value);
	// else if (value == ">" && (i == 1 || i == 2))
	//     printf("%s \`newline\'", error);
}
*/


void	ft_putstr_err(char *error, char *value, t_keyword type, int count)
{
	if (type == APPEND && count == 3)
		printf("%s `>'\n", ERROR);
	if (type == APPEND && count > 3)
		printf("%s `>>'\n", ERROR);
	if (type == HERDOC && count == 3)
		printf("%s `newline'\n", ERROR);
	if (type == HERDOC && count == 4)
		printf("%s `<'\n", ERROR);
	if (type == HERDOC && count == 5)
		printf("%s `<<'\n", ERROR);
	if (type == HERDOC && count > 5)
		printf("%s `<<<'\n", ERROR);
}

// you will cath temp->type make loop on it and check if type >>> or >>>> 
//