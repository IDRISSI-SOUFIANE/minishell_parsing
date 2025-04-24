/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grabage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:58:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:28:06 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_tokens(t_token *tokens)
{
	t_token *tmp;
	int i;

	i = 0;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;

		if (tmp->value)
		{
			i = 0;
			while (tmp->value[i])
			{
				free(tmp->value[i]);
				i++;
			}
			free(tmp->value);
		}

		free(tmp);
	}
}
t_token *deldum(t_token **head)
{
	t_token *temp;
	int i;

	i = 0;
	if (!head || !*head)
		return (NULL);
	temp = *head;
	*head = (*head)->next;

	if (temp->value)
	{
		i = 0;
		while (temp->value[i])
		{
			free(temp->value[i]);
			i++;
		}
		free(temp->value);
	}
	free(temp);
	return (*head);
}

void free_data(t_data *data)
{
	t_var_data	d_var;

	ft_memset(&d_var, 0, sizeof(d_var));
	d_var.current = data;
	while (d_var.current)
	{
		d_var.next = d_var.current->next;
		free(d_var.current->cmd);
		if (d_var.current->args)
		{
			d_var.i = 0;
            while (d_var.current->args[d_var.i])
                free(d_var.current->args[d_var.i++]);
            free(d_var.current->args);
        }
		d_var.redir = d_var.current->file;
        while (d_var.redir)
        {
			d_var.next_redir = d_var.redir->next;
			(free(d_var.redir->name),free(d_var.redir));
            d_var.redir = d_var.next_redir;
        }
        free(d_var.current);
        d_var.current = d_var.next;
    }
}