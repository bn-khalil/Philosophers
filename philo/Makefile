# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 22:10:16 by kben-tou          #+#    #+#              #
#    Updated: 2025/04/15 22:10:19 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MANDATORY_DIR = src/
HEADER = $(MANDATORY_DIR)philo.h
SRC = $(MANDATORY_DIR)philo.c \
	  $(MANDATORY_DIR)philo_creates.c \
	  $(MANDATORY_DIR)philo_parsing.c \
	  $(MANDATORY_DIR)philo_utils.c \
	  $(MANDATORY_DIR)philo_initial.c \
	  $(MANDATORY_DIR)philo_exec.c \

OBJS = $(SRC:.c=.o)
CFLAGS =  -Wall -Wextra -Werror -g -fsanitize=address  # malloc sdfsd fsanitize remove

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all