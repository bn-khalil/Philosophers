# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 22:10:16 by kben-tou          #+#    #+#              #
#    Updated: 2025/04/19 11:40:17 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
MANDATORY_DIR = src/
HEADER = inc/philo_bonus.h

SRC = $(MANDATORY_DIR)philo_bonus.c \
	  $(MANDATORY_DIR)philo_parsing_bonus.c \
	  $(MANDATORY_DIR)philo_utils_bonus.c \
	  $(MANDATORY_DIR)philo_creates_bonus.c \
	  $(MANDATORY_DIR)philo_initial_bonus.c \
	  $(MANDATORY_DIR)philo_execute_bonus.c \
	  $(MANDATORY_DIR)philo_habits_bonus.c \
	  $(MANDATORY_DIR)philo_tools_bonus.c \

OBJS = $(SRC:.c=.o)
CFLAGS =  -Wall -Wextra -Werror #-fsanitize=thread  # malloc sdfsd fsanitize remove

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