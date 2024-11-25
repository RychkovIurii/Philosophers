# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:48:09 by irychkov          #+#    #+#              #
#    Updated: 2024/11/25 16:05:27 by irychkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = main_bonus.c parse_input_bonus.c init_data_bonus.c errors_bonus.c

OBJS = $(SRCS:.c=.o)

.SECONDARY: $(OBJS)

HEADERS = -I.

CFLAGS = -Wall -Wextra -Werror -g #-lpthread -g

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
