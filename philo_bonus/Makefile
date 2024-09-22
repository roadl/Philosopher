# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojin <yojin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 13:12:14 by yojin             #+#    #+#              #
#    Updated: 2024/08/15 19:39:08 by yojin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
LDIR = ./
HEADER = ./philo_bonus.h
SRCS = philo_bonus.c init_bonus.c philo_util_bonus.c \
		sem_bonus.c debug_bonus.c philo_thread_bonus.c
OBJS = $(SRCS:.c=.o)
NAME = philo_bonus

args = 4 410 200 200

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -I$(LDIR)

bonus: $(BONUS_OBJS)
	touch bonus
	$(CC) $(CFLAGS) $^ -o $(NAME) -I$(LDIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LDIR)

re: fclean all

clean:
	rm -f bonus
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

drd: $(NAME)
	valgrind --tool=drd -s \
    --trace-mutex=yes \
    --trace-semaphore=yes \
    --trace-fork-join=yes \
    --exclusive-threshold=10 \
    ./$(NAME) $(args)

.PHONY: all re clean fclean
