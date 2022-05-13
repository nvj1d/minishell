NAME = minishell

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRCS = ./src/main.c ...

OBJS = $(SRCS:.c=.o)

HEADER = ./src/minishell.h

LIBFT = ./src/libft/libft.a

all : $(NAME)

#is the header here!?
$(NAME) : $(OBJS) $(HEADER) 
  $(MAKE) -C ./libft
  echo "making libft.a" #with the bonus!
  $(CC) $(FLAGS) ${LIBFT} -o $@

%.o : %.c
  $(CC) $(FLAGS) -I $(HEADER) -c $< -o $@
  
  #bonus : $(OBJS_B)
  
  clean :
    $(MAKE) clean -C ./libft
    rm -rf $(OBJS)
  
  fclean :  clean
    $(MAKE) fclean -C ./libft
    rm -rf $(NAME)
 
 re : fclean $(NAME)
