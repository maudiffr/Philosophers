# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 13:14:25 by maudiffr          #+#    #+#              #
#    Updated: 2024/03/01 11:06:46 by maudiffr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

SRC = main.c args.c init.c routine.c forks.c keeper.c exit.c
      
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
