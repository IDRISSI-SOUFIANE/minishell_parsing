/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:50:21 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:50:23 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *ft_lstnew_p(void)
{
	t_data *new_node = malloc(sizeof(t_data));
	if (!new_node)
		return (NULL);
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->file = NULL;
	new_node->next = NULL;
	return (new_node);
}