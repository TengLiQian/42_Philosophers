# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lteng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 13:33:21 by lteng             #+#    #+#              #
#    Updated: 2024/07/10 21:19:50 by lteng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c philo_utils.c philo_utils2.c philo_init.c philo_dinner.c \
	philo_threads.c philo_monitor.c

OBJS = $(SRCS:.c=.o)
CC = cc -g
CFLAGS = -Wall -Werror -Wextra
NAME = philo
RM = rm -rf
all: $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
