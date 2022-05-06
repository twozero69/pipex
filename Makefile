# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 17:31:10 by younglee          #+#    #+#              #
#    Updated: 2022/05/06 08:24:32 by younglee         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= @cc
CFLAGS		= -Wall -Wextra -Werror -g
M_SRCS		= srcs/main.c \
			srcs/init_pipex.c \
			srcs/start_pipex.c \
			srcs/end_pipex.c \
			srcs/free_all.c \
			srcs/error.c \
			srcs/check_cmd_path.c \
			srcs/close_fd.c
M_OBJS		= ${M_SRCS:.c=.o}
B_SRCS		= bonus/main_bonus.c
B_OBJS		= ${B_SRCS:.c=.o}
INC			= -I./includes
RM			= @rm -f
LIBFT		= -L./libft -lft
LIBFT_INC	= -I./libft
LIBFT_LIB	= libft/libft.a

ifndef WITH_BONUS
	OBJS	= ${M_OBJS}
else
	OBJS	= ${B_OBJS}
endif

.c.o:
			${CC} ${CFLAGS} ${INC} ${LIBFT_INC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${LIBFT_LIB}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

all:		${NAME}

${LIBFT_LIB}:
			@make -C libft

clean:
			${RM} ${M_OBJS} ${B_OBJS}
			@make clean -C libft

fclean:		clean
			${RM} ${NAME} ${LIBFT_LIB}

re:			fclean all

# bonus:
# 			@make WITH_BONUS=1 all

.PHONY:		all clean fclean re bonus
