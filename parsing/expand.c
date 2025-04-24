/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:29:27 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 09:32:44 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_double_quote(t_expand *ex, char *str)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '"')
	{
		if (str[ex->i] == '$')
		{
			process_dollar(ex, str);
		}
		else
		{
			append_char(ex, str[ex->i]);
			ex->i++;
		}
	}
	if (str[ex->i] == '"')
		ex->i++;
}

char **split(t_expand *ex, int *flag)
{
	char **result;

	//printf("==>flag: %d\n", *flag);

	if (*flag == 0)
	{
		result = ft_split(ex->res, ' ');
		free(ex->res);
	}
	else
	{
		result = malloc(2 * sizeof(char *));
		if (!result)
		{
			free(ex->res);
			return (NULL);
		}
		result[0] = ex->res;
		result[1] = NULL;
	}
	return (result);
}

char **expand_string(char *str, int *flag)
{
	t_expand ex;

	ft_memset(&ex, 0, sizeof(ex));
	ex.res = ft_strdup("");
	if (!ex.res)
		return (NULL);
	while (str[ex.i])
	{
		if (str[ex.i] == '\'')
			handle_single_quote(&ex, str, flag);
		else if (str[ex.i] == '"')
		{
			handle_double_quote(&ex, str);
			*flag = 1;
		}
		else if (str[ex.i] == '$')
			process_dollar(&ex, str);
		else
		{
			append_char(&ex, str[ex.i]);
			ex.i++;
		}
	}
	return (split(&ex, flag));
}

int	ft_null(char *s)
{
	char	*s_q;
	char	*d_q;

	d_q = "\"\"";
	s_q = "\'\'";
	if (!ft_strcmp(s, s_q) || !ft_strcmp(s, d_q))
		return (1);
	return (0);
}

void ft_expand(t_token *tokens, int i)
{
	char **expanded;
	int flag;

	while (tokens)
	{
		if (tokens->type != F_HERDOC && tokens->value
			&& tokens->value[0] && !ft_null(tokens->value[0]))
		{
			flag = 0;
			expanded = expand_string(tokens->value[0], &flag);
			if (tokens->value)
			{
				i = 0;
				while (tokens->value[i])
				{
					free(tokens->value[i]);
					i++;
				}
				i = 0;
				free(tokens->value);
			}
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
