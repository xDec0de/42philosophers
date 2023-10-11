# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danimart <danimart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 16:29:48 by danimart          #+#    #+#              #
#    Updated: 2023/10/11 17:47:33 by danimart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
CC=gcc

MAX_PHILOSOPHERS?=200
DEBUG?=0

C_FILES=philosophers.c input_parser.c philo_builder.c philo_handler.c mutex_helper.c philo_utils.c
CFLAGS=-DMAX_PHILOSOPHERS='$(MAX_PHILOSOPHERS)' -DDEBUG='$(DEBUG)' -Wall -Werror -Wextra -pthread

O_FILES=$(C_FILES:.c=.o)

all: $(NAME)
$(NAME): $(O_FILES)
	@printf "\n\e[0;33m-\e[1;32m "
	$(CC) $(C_FLAGS) $(O_FILES) -o $(NAME)
	@printf "\n\033[0m"
clean:
	@printf "\n\e[0;33m-\e[1;32m "
	rm -rf $(O_FILES)
	@printf "\n\033[0m"
fclean:
	@printf "\n\e[0;33m-\e[1;32m "
	rm -rf $(NAME) $(O_FILES)
	@printf "\n\033[0m"
re: fclean $(NAME)
.PHONY: all clean fclean re