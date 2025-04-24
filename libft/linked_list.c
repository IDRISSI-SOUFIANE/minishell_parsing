/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:11:15 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/06 13:08:05 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *ft_lstlast(t_token *lst)
{
	t_token *tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void ft_lstadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_token *ft_lstnew(char *content, t_keyword type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);

	new->value = malloc(2 * sizeof(char *));
	if (!new->value)
	{
		free(new);
		return (NULL);
	}

	new->value[0] = content;
	if (!new->value[0])
	{
		free(new->value);
		free(new);
		return (NULL);
	}
	new->value[1] = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}
