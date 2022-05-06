# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: younglee <younglee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/01 17:31:10 by younglee          #+#    #+#              #
#    Updated: 2022/05/07 08:34:09 by younglee         ###   ########seoul.kr   #
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
			srcs/close_fd.c \
			srcs/wait_all_child.c
M_OBJS		= ${M_SRCS:.c=.o}
B_SRCS		= bonus/main_bonus.c \
			bonus/init_pipex_bonus.c \
			bonus/start_pipex_bonus.c \
			bonus/end_pipex_bonus.c \
			bonus/free_all_bonus.c \
			bonus/error_bonus.c \
			bonus/check_cmd_path_bonus.c \
			bonus/close_fd_bonus.c \
			bonus/wait_all_child_bonus.c \
			bonus/middle_pipex_bonus.c \
			bonus/here_doc_pipex_bonus.c
B_OBJS		= ${B_SRCS:.c=.o}
INC			= -I./includes
RM			= @rm -f
LIBFT		= -L./libft -lft
LIBFT_INC	= -I./libft
LIBFT_LIB	= libft/libft.a
GNL_SRCS	= get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c
GNL_OBJS	= ${GNL_SRCS:.c=.o}
GNL_INC		= -I./get_next_line

ifndef WITH_BONUS
	OBJS	= ${M_OBJS}
else
	OBJS	= ${B_OBJS}
endif

.c.o:
			${CC} ${CFLAGS} ${INC} ${LIBFT_INC} ${GNL_INC} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${LIBFT_LIB} ${GNL_OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${GNL_OBJS}

all:		${NAME}

${LIBFT_LIB}:
			@make -C libft

clean:
			${RM} ${M_OBJS} ${B_OBJS}
			@make clean -C libft

fclean:		clean
			${RM} ${NAME} ${LIBFT_LIB}

re:			fclean all

bonus:
			@make WITH_BONUS=1 all

norm:
			@norminette srcs/*.[ch] includes/*.[ch] bonus/*.[ch]

.PHONY:		all clean fclean re bonus norm
