/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:22:56 by sidrissi          #+#    #+#             */
/*   Updated: 2025/04/24 11:08:38 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h> 

#define ERROR "syntax error near unexpected token\n"
#define name_length 9

typedef enum s_keyword
{
	WRITE_OUT,
	READ_IN,
	APPEND,
	HERDOC,
	PIPE,
	PIPES,
	WORD,
	START,
	FREAD_IN,
	FWRITE_OUT,
	F_HERDOC,
	F_APPEND,
	CMD,
} t_keyword;

typedef struct s_quote_data
{
	char *line;
	int *i;
	char **buffer;
} t_quote_data;

typedef	struct s_initalize
{
	int		j;
	char	quote;
    char	*new_buffer;
	char	*res;
}	t_initalize;

typedef struct s_token
{
	char 			**value;
	int				fd;
	t_keyword 		type;
	struct s_token 	*next;
} t_token;

typedef struct s_expand
{
	char *res;
	int i;
	int dollar_count;
	int var_len;
	char *var_name;
} t_expand;

/*              ******************************************************************************************        */
typedef struct s_redir
{
	char			*name;
	int				fd;
	t_keyword		type;
	struct s_redir 	*next;
} t_redir;

typedef struct s_data
{
	char *cmd;
	char **args;
	t_redir *file;
	struct s_data *next;
} t_data;


// free in file garbage.c
typedef struct	s_var_data
{
	t_data *current;
	t_data *next;
	t_redir *redir;
	t_redir *next_redir;
	int		i;
}	t_var_data;

/*********************Parsing**********************/

/*main.c*/
int check_quotes(char *line, int i, int count_quote);
t_token *lexing(char *line, int *flag);
// void lexing(char *line);

/*---------------tokenization---------------*/
int sp(char c);
t_token *tokenization(char *line, int i);
void	handle_quotes(t_quote_data *data, t_initalize *init);
/*---------------garbage---------------*/
// Linked list:
void free_tokens(t_token *tokens);
t_token *deldum(t_token **head);
void free_data(t_data *data);

/*---------------error---------------*/
int	error(t_token *tokens , t_token *current);
int	is_redirect(t_keyword type);
int	is_pipe(t_keyword type);
int	pipe_check(t_token *prev, t_token *next);

/*---------------expand---------------*/
void ft_expand(t_token *tokens, int i);
void handle_single_quote(t_expand *ex, char *str, int *flag);
void process_dollar(t_expand *ex, char *str);
void handle_odd_dollars(t_expand *ex, char *str);
void extract_var(t_expand *ex, char *str);
void handle_even_dollars(t_expand *ex);
void append_char(t_expand *ex, char c);

/*---------------ft_rename------------*/
void ft_rename(t_token *tokens);

/*-------------ft_herdoc--------------*/
void ft_herdoc(t_token **tokens);
char **ft_expand_herdoc(char *str, int *flag);
void handle_odd_dollars_herdoc(t_expand *ex, char *str);
void extract_var_herdoc(t_expand *ex, char *str);
void handle_even_dollars_herdoc(t_expand *ex);
void append_char_herdoc(t_expand *ex, char c);

/*-------------parsing--------------*/
t_data *parsing(t_token **tokens, t_token *temp);
t_data *ft_lstnew_p(void);

/*===============libft===============*/
char *ft_substr(char *s, int start, int len);
void ft_putstr_fd(char *s, int fd);
int ft_strlen(char *s);
char *ft_strdup(char *s);
int ft_isprint(int c);
int ft_cmp(char *word);
char *ft_strjoin(char *s1, char *s2);
// Linked list:
t_token *ft_lstlast(t_token *lst);
t_token *ft_lstnew(char *content, t_keyword type);
void ft_lstadd_back(t_token **lst, t_token *new);

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
void *ft_memset(void *b, int c, size_t len);
int ft_strcmp(char *s1, char *s2);

/***************ft_split************* */
void *ft_free(char **strs, int count);
char **ft_split(char *s, char c);

/* just remove them cause we don't use them*/
// int		ft_strncmp(char *s1, char *s2, int n);/*not use it check before remove it */
// char	*ft_strndup(char *s, size_t n);/*not use it check before remove it */
// char	*ft_allocate(char **res, int len);/*not use it check before remove it */
// char	*ft_strcat(char *dest, char *src);/*not use it check before remove it */
// char	*ft_strncpy(char *dest, char *src, int n);/*not use it check before remove it */

#endif