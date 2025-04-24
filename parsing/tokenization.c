/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:54:18 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:58:33 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_words(char *line, int *i, char **buffer)
{
	int	j;
    char    *new_word;
    char    *new_buffer;
	
	j = *i;
	while (line[*i] && !sp(line[*i]) && line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
    new_word = ft_substr(line, j, (*i - j));
    if (!new_word)
        return ;
    if (*buffer == NULL)
        *buffer = new_word;
    else
    {
        new_buffer = ft_strjoin(*buffer, new_word);
        free(new_word);
        free(*buffer);
        *buffer = new_buffer;
    }
}

t_initalize	*ft_initialize()
{
	t_initalize	*init;

	init = malloc(sizeof(t_initalize));
	if (NULL == init)
		return (NULL);
	init->j = 0;
	init->new_buffer = NULL;
	init->res = NULL;
	init->quote = '\0';
	return (init);
}

void handle_mixed_words(char *line, int *i, t_token **head)
{
	char *buffer;
	t_initalize	*init;

    buffer = NULL;
	init = ft_initialize();
	while (line[*i] && !sp(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			handle_quotes(&(t_quote_data){line, i, &buffer}, init);
		else
			handle_words(line, i, &buffer);
	}
    if (buffer)
		ft_lstadd_back(head, ft_lstnew(buffer, WORD));
	free(init);
}

void handle_special_chars(char *line, int *i, t_token **head)
{
	char *sp_char;
	int j;

	j = *i;
	while (line[*i] && line[*i] == line[j])
		(*i)++;
	sp_char = ft_substr(line, j, *i - j);

	if (ft_cmp(sp_char) == PIPE)
		ft_lstadd_back(head, ft_lstnew(sp_char, PIPE));
	else if (ft_cmp(sp_char) == PIPES)
		ft_lstadd_back(head, ft_lstnew(sp_char, PIPES));
	else if (ft_cmp(sp_char) == WRITE_OUT)
		ft_lstadd_back(head, ft_lstnew(sp_char, WRITE_OUT));
	else if (ft_cmp(sp_char) == APPEND)
		ft_lstadd_back(head, ft_lstnew(sp_char, APPEND));
	else if (ft_cmp(sp_char) == READ_IN)
		ft_lstadd_back(head, ft_lstnew(sp_char, READ_IN));
	else if (ft_cmp(sp_char) == HERDOC)
		ft_lstadd_back(head, ft_lstnew(sp_char, HERDOC));
	else
		free(sp_char);
}

t_token *tokenization(char *line, int i)
{
	t_token *head;

	head = ft_lstnew(ft_strdup("."), START);
	if (!head)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			handle_mixed_words(line, &i, &head);
		else if (sp(line[i]))
		{
			if (line[i] == ' ')
				i++;
			else
				handle_special_chars(line, &i, &head);
		}
		else
			handle_mixed_words(line, &i, &head);
	}
	head = deldum(&head);
	return (head);
}
