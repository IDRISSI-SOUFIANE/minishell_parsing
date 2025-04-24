/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rename.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:41:05 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:26:48 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_redirection(t_keyword type)
{
	return (type == PIPE || type == READ_IN || type == WRITE_OUT
		|| type == APPEND || type == HERDOC);
}

void ft_redierct(t_token *prev, t_token *tokens)
{
	if (prev->type == READ_IN)
		tokens->type = FREAD_IN;
	else if (prev->type == WRITE_OUT)
		tokens->type = FWRITE_OUT;
	else if (prev->type == APPEND)
		tokens->type = F_APPEND;
	else if (prev->type == HERDOC)
		tokens->type = F_HERDOC;
	else if (prev->type == PIPE)
		tokens->type = CMD;
}

void ft_rename(t_token *tokens)
{
	t_token *prev;
	int cmd_found;

	cmd_found = 0;
	prev = NULL;
	while (tokens)
	{
		if (tokens->type == WORD && prev && is_redirection(prev->type))
			ft_redierct(prev, tokens);
		else if (tokens->type == WORD && !cmd_found)
		{
			tokens->type = CMD;
			cmd_found = 1;
		}
		prev = tokens;
		tokens = tokens->next;
	}
}
