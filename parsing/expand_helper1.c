/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:32:53 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 09:48:21 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_even_dollars(t_expand *ex)
{
	int num;
	char *dollars;
	char *new_res;

	num = ex->dollar_count / 2;
	dollars = malloc(num + 1);
	if (!dollars)
		return;
	ft_memset(dollars, '$', num);
	dollars[num] = '\0';
	new_res = ft_strjoin(ex->res, dollars);
	free(ex->res);
	free(dollars);
	ex->res = new_res;
}

void extract_var(t_expand *ex, char *str)
{
	int start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}

void handle_odd_dollars(t_expand *ex, char *str)
{
	char *val;
	char *new_res;

	if (ft_isalnum(str[ex->i]) || str[ex->i] == '_') // || ?
	{
		extract_var(ex, str);
		val = getenv(ex->var_name); // if I remove the export should check if THERE is NO EXPORT TO PREVENT THE SEGV
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
}

void process_dollar(t_expand *ex, char *str)
{
	ex->dollar_count = 0;
	while (str[ex->i] == '$')
	{
		ex->dollar_count++;
		ex->i++;
	}
	if (ex->dollar_count % 2)
		handle_odd_dollars(ex, str);
	else
		handle_even_dollars(ex);
}

void handle_single_quote(t_expand *ex, char *str, int *flag)
{
	ex->i++;
	while (str[ex->i] && str[ex->i] != '\'')
	{
		append_char(ex, str[ex->i]);
		ex->i++;
	}
	if (str[ex->i] == '\'')
		ex->i++;
	*flag = 1;
}