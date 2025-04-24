/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_expand_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:00:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:00:39 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void append_char_herdoc(t_expand *ex, char c)
{
	char *new_res;
	char tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new_res = ft_strjoin(ex->res, tmp);
	free(ex->res);
	ex->res = new_res;
}

void handle_even_dollars_herdoc(t_expand *ex)
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

void extract_var_herdoc(t_expand *ex, char *str)
{
	int start;

	ex->var_len = 0;
	start = ex->i;
	while (ft_isalnum(str[ex->i]) || str[ex->i] == '_')
	{
		ex->i++;
		ex->var_len++;
	}
	ex->var_name = ft_substr(str, start, ex->var_len);
}

void handle_odd_dollars_herdoc(t_expand *ex, char *str)
{
	char *val;
	char *new_res;

	if (ft_isalnum(str[ex->i]) || str[ex->i] == '_')
	{
		extract_var_herdoc(ex, str);
		val = getenv(ex->var_name);
		if (!val)
			val = "";
		new_res = ft_strjoin(ex->res, val);
		free(ex->res);
		free(ex->var_name);
		ex->res = new_res;
	}
}