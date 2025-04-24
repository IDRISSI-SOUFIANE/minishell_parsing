/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:01:21 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/17 03:35:54 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	is_sep(char s, char c)
{
	return (s == c);
}

static char	*fill_word(char *s, int *preffix, char c)
{
	char	*word;
	int		i;
	int		len_word;

	len_word = 0;
	i = *preffix;
	while (s[i] && is_sep(s[i], c))
		i++;
	*preffix = i;
	while (s[i] && !(is_sep(s[i], c)))
	{
		len_word++;
		i++;
	}
	word = malloc((len_word + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len_word)
		word[i++] = s[(*preffix)++];
	word[i] = '\0';
	return (word);
}

static int	word_count(char *s, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep(s[i], c))
		{
			words++;
			while (s[i] && !is_sep(s[i], c))
				i++;
		}
		else
			i++;
	}
	return (words);
}

char	**ft_split(char *s, char c)
{
	char	**word_arr;
	int		number_words;
	int		i;
	int		preffix;

	if (!s)
		return (NULL);
	preffix = 0;
	number_words = word_count(s, c);
	word_arr = (char **)malloc((number_words + 1) * sizeof(char *));
	if (!word_arr)
		return (NULL);
	i = 0;
	while (i < number_words)
	{
		word_arr[i] = fill_word(s, &preffix, c);
		if (!word_arr[i])
			return (ft_free(word_arr, i));
		i++;
	}
	word_arr[i] = NULL;
	return (word_arr);
}
