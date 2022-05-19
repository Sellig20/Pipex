# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 13:33:46 by jecolmou          #+#    #+#              #
#    Updated: 2022/05/19 13:54:30 by jecolmou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	pipex

SRCS					=	pipex.c \
							parent.c \
							parents_annexe.c \
							childs.c \
							path_command.c \
							tools.c \
							free.c \
							parsing.c \
							libft/ft_split.c \
							libft/ft_strnstr.c \
							libft/ft_strjoin.c \
							libft/ft_strlen.c \
							libft/ft_putstr_fd.c \
							libft/ft_strcmp.c \

OBJS					=	${SRCS:.c=.o}

CC						=	clang

CFLAGS					=	-Wall -Wextra -Werror -g3

RM						=	rm -rf

all		:	${NAME}

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o		:	%.c
		$(CC) $(CFLAGS)	-c	$<	-o	$@

clean	:
		${RM}	${OBJS}

fclean	:	clean
		${RM}	${NAME}

re:	fclean	all

malloc_test: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} -L. -lmallocator

.PHONY:	all	clean	fclean	re
