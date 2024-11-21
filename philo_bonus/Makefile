# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:48:09 by irychkov          #+#    #+#              #
#    Updated: 2024/11/21 17:08:01 by irychkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = main_bonus.c parse_input_bonus.c errors_bonus.c

OBJS = $(SRCS:.c=.o)

.SECONDARY: $(OBJS)

HEADERS = -I.

CFLAGS = -Wall -Wextra -Werror #-lpthread -g

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compiled philo_bonus: $(NAME)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	@rm -rf $(OBJS)
	@echo "Cleaned object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Fully cleaned"

re: fclean all

.PHONY: all clean fclean re
