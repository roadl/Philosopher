# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojin <yojin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 13:12:14 by yojin             #+#    #+#              #
#    Updated: 2024/08/15 19:56:45 by yojin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
LDIR = ./
HEADER = ./philo.h
SRCS = philo.c init.c philo_util.c mutex.c philo_thread.c
OBJS = $(SRCS:.c=.o)
NAME = philo

args = 4 410 200 200

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -I$(LDIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LDIR)

re: fclean all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
.PHONY: all re clean fclean
