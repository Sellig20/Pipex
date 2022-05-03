# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 13:33:46 by jecolmou          #+#    #+#              #
#    Updated: 2022/04/30 15:38:47 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            =       pipex

SRCS            =		pipex.c \
						libft/ft_split.c \
						libft/ft_strnstr.c \
						libft/ft_strjoin.c \
						libft/ft_strlen.c \
						childs.c \
						tools.c \

OBJS            =       ${SRCS:.c=.o}

CC                      =       gcc

CFLAGS          		=       -Wall -Wextra -Werror

RM                      =       rm -rf

all:	${NAME}

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS)	-c	$<	-o	$@

clean:
		${RM}	${OBJS}

fclean: clean
		${RM}	${NAME}

re:	fclean	all

.PHONY:	all	clean	fclean	re
