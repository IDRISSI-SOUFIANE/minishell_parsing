/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:46 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 12:39:22 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int check_quotes(char *line, int i, int count_quote)
{
	char quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			count_quote++;
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				count_quote++;
			else
				break;
			i++;
		}
		else
			i++;
	}
	if (count_quote % 2)
		return (1);
	return (0);
}

t_token *lexing(char *line, int *flag)
{
	int		i;
	int		count_quote;
	t_token	*tokens;
	t_token	*current;

	i = 0;
	count_quote = 0;
	if (check_quotes(line, i, count_quote))
		return (ft_putstr_fd("missing quotation\n", 2), NULL);

	tokens = tokenization(line, i);
	if (tokens == NULL)
		return (NULL);
	tokens->fd = 0;
	current = NULL;
	if (error(tokens, current))
	{
		*flag = 1;
		return (tokens);
	}
	ft_rename(tokens);
	ft_expand(tokens, i);
	ft_herdoc(&tokens);
	return (tokens);
}



// void ft_excution(t_data *data)
// {
// 	/*		printe cause leaks				*/
// 			// PRINT
// 			t_data *tmp = data;
// 			while (tmp)
// 			{

// 				printf("\n\n");
// 				printf("Command: %s\n", tmp->cmd ? tmp->cmd : "(no command)");

// 				// Print arguments
// 				printf("Arguments:");
// 				if (tmp->args)
// 				{
// 					// printf("tmp->arg[1]: %s\n", tmp->args[1]);
// 					for (int i = 0; tmp->args[i]; i++)
// 						printf(" |%s|", tmp->args[i]);
// 				}
// 				//Print files
// 				printf("\n");
// 				if (tmp->file)
// 				{
// 					while (tmp->file)
// 					{
// 						if (tmp->file->type != F_HERDOC)
// 						{
// 							printf("[fname: %s | ftype: %d]\n",  (tmp->file->name), tmp->file->type);
// 							free(tmp->file->name);
// 						}
// 						else
// 						{
// 							// if (tmp->file->fd < 0)
// 							// {
// 							// 	printf("error in fd \n");
// 							// 	return ;
// 							// }
// 							printf("[fd: %d | ftype: %d]\n",  (tmp->file->fd), tmp->file->type);
							
// 								char	buffer[1337];
// 								int		reads_size;
// 								if (tmp->file->fd < 0)
// 									printf("fd is failed\n");
								


// 								reads_size = read(tmp->file->fd, buffer, 1337);
// 								printf("reads_size: %d\n", reads_size);
								
// 								buffer[reads_size] = '\0';
								
// 								printf("buffer: %s\n", buffer);
// 								if (reads_size <= 0)
// 									printf("reads_size read nothing\n");
// 						}
						
// 						tmp->file = tmp->file->next;
// 					}
					
// 				}
// 				tmp = tmp->next;
// 			}
// }



void	f()
{
	system("leaks minishell");
}


void	helper_main(t_token *tokens, int *flag)
{
	t_data	*data;
	t_token *temp;

	temp = NULL;
	if (*flag == 0)
	{
		data = parsing(&tokens, temp);
		//	execution
			// ft_excution(data);
		//
		free_data(data);
		free_tokens(tokens);
	}
	else
	{
		free_tokens(tokens);
	}
}

int main(int ac, char **av, char **env)
{
	atexit(f);
	((void)ac, (void)av);
	(void)env; // I am voiding env cause in expand i am using function getenv() !!!!! and should check if env is not NULL also should work with env of execution

	char	*line;
	int		flag;
	t_token	*tokens;

	while (1)
	{
		flag = 0;
		line = readline("Minishell: ");
		if (line == NULL)
		{
			// free_data(data);
			// free_tokens(tokens);
			break;
		}
		tokens = lexing(line, &flag);
		helper_main(tokens, &flag);
		
		if (line[0] != '\0')
			add_history(line);
		//		test: lexing(line);

		free(line);
		// flag = 0;
	}
	return (0);
}





































































/* Problem
	the problem the leaks maybe 89% in free_data => when we call multiple file maybe we are not free the previous allocation of these files
	the test: < a < b < c > d

*/







































































































// void	lexing(char *line)
// {
// 	int		i;
// 	int		count_quote;
// 	t_token	*tokens;

// 	i = 0;
// 	count_quote = 0;
// 	if (check_quotes(line, i, count_quote))
// 		return (ft_putstr_fd("missing quotation\n", 2));

// 	tokens = tokenization(line, i);
// 	if (tokens == NULL)
// 		return ;
// 	// error(tokens);
// 	// ft_rename(tokens);
// 	// ft_expand(tokens);
// 	// ft_herdoc(tokens);

// 	t_token *temp;

// 	temp = tokens;

// 	// printf("@==> %s\n", temp->value[0]);

// 	while (temp)
// 	{
// 		int	i = 0;
// 		if (temp->value)
// 		{
// 			while (temp->value[i])
// 			{
// 					printf("\n | %s |\n", temp->value[i]);
// 					i++;
// 			}
// 		}
// 		temp = temp->next;
// 	}

// }



/*************************************/
//  handle this cas '' '' '' ''  
// add `command` as argument also, cause execve need it


/* problem
	syntax error ;;
*/

/*
there still a problem when i write '           ' => the problem is not print l espace
exept when somethig in single_quote like this => '        .'
so should fix this issue when i have a space in single quote should keep the space '      '
*/

/* 
	problem in herdoc "ok" => khaso irooj bi ok bla ""
	check this in your bash and compare it with real bash
*/

/* problem
<< ok |||| << d
check this in your bash and compare it with real bash
*/

/* problem
	close(fd) => if I close it fd in parsing the executer can't open it again will lose so be carefule and find a solution 
*/


/* problem
	in expand should handle numberes
*/

