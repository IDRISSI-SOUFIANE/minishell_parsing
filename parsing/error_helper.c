/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:16:30 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 09:22:03 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(t_keyword type)
{
	return (type == READ_IN || type == WRITE_OUT
		|| type == APPEND || type == HERDOC);
}

int	is_pipe(t_keyword type)
{
	return (type == PIPE || type == PIPES);
}

int	pipe_check(t_token *prev, t_token *next)
{
	if (!prev || !next)
		return (1);
	if (next->type == PIPE)
		return (1);
	return (0);
}