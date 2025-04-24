/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:43:23 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:50:30 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add(t_data *current, t_redir *last, t_redir *new_redir)
{
	if (!current->file)
		current->file = new_redir;
	else
	{
		last = current->file;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

void add_redirection(t_data *current, t_token **tokens)
{
	t_redir *new_redir;
	t_redir *last;
	t_token *token;

	last = NULL;
	token = *tokens;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	if (token->type == F_HERDOC)
	{
		new_redir->fd = token->fd;
		new_redir->name = NULL;
	}
	else
	{
		new_redir->name = ft_strdup(token->value[0]);
		new_redir->fd  = -101;
	}
	new_redir->type = token->type;
	new_redir->next = NULL;
	ft_add(current, last, new_redir);
}

void add_argument(t_data *current, char *arg)
{
	int count;
	int i;
	char **new_args;

	count = 0;
	i = 0;
	if (current->args)
		while (current->args[count])
			count++;
	new_args = malloc((count + 2) * sizeof(char *));
	if (!new_args)
		return ;
	while (i < count)
	{
		new_args[i] = current->args[i];
		i++;
	}
	i = 0;
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(current->args);
	current->args = new_args;
}

void	ft_check(t_data *current, t_token *temp)
{
	int	j;
	int i;

	i = 0;
	while (temp->value[i])
		i++ ;
	if (i > 1)
	{
		j = 0;
		while (j < i)
		{
			add_argument(current, temp->value[j]);
			j++;
		}
	}
	else
		add_argument(current, temp->value[0]);
}

t_data *parsing(t_token **tokens, t_token *temp)
{
	t_data *lst;
	t_data *current;

	temp = *tokens;
	lst = ft_lstnew_p();
	current = lst;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			current->next = ft_lstnew_p();
			current = current->next;
		}
		else if (temp->type == CMD)
		{
			current->cmd = ft_strdup(temp->value[0]);
			add_argument(current, temp->value[0]);
		}
		else if (temp->type == WORD)
			ft_check(current, temp);
		else if (temp->type >= FREAD_IN && temp->type <= F_APPEND)
			add_redirection(current, &temp);
		temp = temp->next;
	}
	return (lst);
}
