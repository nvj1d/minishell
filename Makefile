# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnajid <mnajid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/14 14:45:17 by mnajid            #+#    #+#              #
#    Updated: 2022/05/14 14:45:18 by mnajid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRCS =	./src/main.c \
		./src/init.c \
		./src/utils/utils1.c \
		./src/utils/utils2.c \
		./src/builtins/export.c \
		./src/envirement/lst_envadd_back.c \
		./src/envirement/lst_envlast.c \
		./src/builtins/env.c \
		./src/builtins/init.c \
		./src/builtins/pwd.c\
		./src/builtins/echo.c\
		./src/builtins/cd.c\
		./src/builtins/parse.c\
		./src/builtins/unset.c\
		./src/builtins/exit.c\
		./src/builtins/export_utils.c \
		
# 				./src/parser/dollar.c\
# 				./src/parser/pipe.c\
# 				./src/parser/parser.c\
# 				./src/parser/pipe2.c\
# 				./src/parser/preparsing.c\
# 				./src/parser/redirection.c\
# 				./src/parser/redirection2.c\
# 				./src/signals/signal.c\
				

OBJS = $(SRCS:.c=.o)

HEADER = ./src/minishell.h

LIBFT = ./src/libft/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
		$(MAKE) -C ./src/libft
		$(MAKE) bonus -C ./src/libft
		echo "making libft.a ..."
		$(CC) $(FLAGS) $(OBJS)  ${LIBFT} -o $(NAME) 
# -lreadline -L /goinfre/mnajid/.brew/opt/readline/lib -I /goinfre/mnajid/.brew/opt/readline/include

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@
	
#bonus : $(OBJS_B)

clean :
	$(MAKE) clean -C ./libft
	rm -rf $(OBJS)

fclean :  clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re : fclean $(NAME)
