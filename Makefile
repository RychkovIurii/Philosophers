# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 14:30:50 by irychkov          #+#    #+#              #
#    Updated: 2024/11/11 17:42:40 by irychkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c parse_input.c

OBJS = $(SRCS:.c=.o)

HEADERS = -I.

CFLAGS = -Wall -Wextra -Werror #-lpthread
CC = cc

all: mandatory

mandatory: .mandatory

.mandatory: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@touch .mandatory
	@echo "Compiled philo: $(NAME)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	@rm -rf $(OBJS)
	@rm -f .mandatory
	@echo "Cleaned object files"

fclean: clean
	@rm -rf $(NAME)
	@echo "Fully cleaned"

re: fclean all

.PHONY: all clean fclean re