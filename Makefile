CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
# FLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = parsing/main.c parsing/tokenization.c parsing/tokenization_helper.c parsing/grabage.c parsing/error.c\
	parsing/error_helper.c parsing/expand.c parsing/expand_helper1.c parsing/expand_helper2.c\
	parsing/ft_rename.c parsing/ft_herdoc.c parsing/ft_herdoc_expand.c parsing/ft_herdoc_expand_helper.c\
	parsing/parsing.c parsing/parsing_helper.c\
	libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_cmp.c libft/ft_strjoin.c\
	libft/linked_list.c libft/ft_substr.c libft/ft_strdup.c libft/ft_isprint.c\
	libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_strncmp.c\
	libft/ft_strndup.c libft/ft_allocate.c libft/ft_strcat.c libft/ft_strncpy.c\
	libft/ft_memset.c libft/ft_strcmp.c libft/ft_split.c\

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

parsing/%.o: parsing/%.c include/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

libft/%.o: libft/%.c include/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
