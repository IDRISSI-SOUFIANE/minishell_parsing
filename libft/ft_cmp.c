/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:05:38 by sidrissi          #+#    #+#             */
/*   Updated: 2025/02/28 12:17:15 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_cmp(char *word)
{
	int i;
	char shape;

	shape = word[0];
	i = 0;
	while (word[i])
		i++;
	if (shape == '|' || shape == '>' || shape == '<')
	{
		if (i == 1 && shape == '|')
			return (PIPE);
		else if (i > 1 && shape == '|')
			return (PIPES);
		else if (i == 1 && shape == '>')
			return (WRITE_OUT);
		else if (i > 1 && shape == '>')
			return (APPEND);
		else if (i == 1 && shape == '<')
			return (READ_IN);
		else if (i > 1 && shape == '<')
			return (HERDOC);
	}
	return (100);
}
