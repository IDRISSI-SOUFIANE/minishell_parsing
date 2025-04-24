/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:57:56 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:58:55 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int sp(char c)
{
	return (c == ' ' || c == '>' || c == '<' || c == '|');
}

void	handle_quotes(t_quote_data *data, t_initalize *init)
{
	init->quote = data->line[*(data->i)];
	init->j = *(data->i);
	(*(data->i))++;
	while (data->line[*(data->i)] && data->line[*(data->i)] != init->quote)
		(*(data->i))++;
	if (data->line[*(data->i)] == init->quote)
	{
		init->res = ft_substr(data->line, init->j, *(data->i) - init->j + 1);
		if (!init->res)
			return ;
		if (init->j == 0)
		{
			free(*(data-> buffer));
			*(data->buffer) = init->res;
		}
		else
		{
			init->new_buffer = ft_strjoin(*(data->buffer), init->res);
			free(init->res);
			free(*(data->buffer));
			*(data->buffer) = init->new_buffer;
		}
		(*(data->i))++;
	}
}