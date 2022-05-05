# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 17:31:10 by younglee          #+#    #+#              #
#    Updated: 2022/05/05 19:08:07 by younglee         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
SRCS		= srcs/main.c \
			srcs/init_pipex.c \
			srcs/start_pipex.c \
			srcs/end_pipex.c \
			srcs/free_all.c \
			srcs/exit_with_error.c \
			srcs/close_fd.c
OBJS		= ${SRCS:.c=.o}
INC			= -I./includes
RM			= rm -f
LIBFT		= -L./libft -lft
LIBFT_INC	= -I./libft
LIBFT_LIB	= libft/libft.a

.c.o:
			${CC} ${CFLAGS} ${INC} ${LIBFT_INC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${LIBFT_LIB}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

all:		${NAME}

${LIBFT_LIB}:
			@make -C libft

clean:
			${RM} ${OBJS}
			@make clean -C libft

fclean:		clean
			${RM} ${NAME} ${LIBFT_LIB}

re:			fclean all

.PHONY:		all clean fclean re
