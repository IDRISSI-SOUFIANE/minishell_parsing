/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:35:54 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 09:36:13 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void append_char(t_expand *ex, char c)
{
	char *new_res;
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(ex->res, tmp);
	free(ex->res);
	ex->res = new_res;
}