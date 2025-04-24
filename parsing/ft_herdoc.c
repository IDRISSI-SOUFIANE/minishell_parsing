/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:40:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 10:25:49 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_herdoc(char *delimter, int helper_fd, int *n)
{
	int 	fd;
	char 	*line;
	char	**exp;
	char	*new_line;

	helper_fd = open("/tmp/random_name", O_RDWR | O_CREAT, 0777);
	fd = open ("/tmp/random_name", O_RDONLY | O_CREAT, 0777);
	if (unlink("/tmp/random_name") || (helper_fd < 0) || (fd < 0))
		return (perror("faile"), close(helper_fd), close(fd), -1);
	while (1)
	{
		line = readline("> ");
		if ((!line) || ft_strcmp(line, delimter) == 0)
		{
			free(line);
			break;
		}
		exp = ft_expand_herdoc(line, n);
		new_line = exp[0];
		(write(helper_fd, new_line, ft_strlen(new_line)), write(helper_fd, "\n", 1));
		(free(line), free(new_line), free(exp));
	}
	return (close(helper_fd), fd); // should close the return file descriptor
}

void ft_herdoc(t_token **tokens)
{
	t_token *current;
	int		fd_;
	int		n;
	int		helper_fd;

	helper_fd = 0;
	n = 42;
	fd_ = -1;
	current = *tokens;
	while (current)
	{
		if (current->type == HERDOC
			&& current->next && current->next->type == F_HERDOC)
		{
			fd_ = open_herdoc(current->next->value[0], helper_fd,  &n);
			if (fd_ != -1)
				current->next->fd = fd_;
		}
		current = current->next;
	}
}

