# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danimart <danimart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 16:29:48 by danimart          #+#    #+#              #
#    Updated: 2023/10/08 17:01:28 by danimart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philosophers
EXEC_NAME=philo
CC=gcc

MAX_PHILOSOPHERS?=200
DEBUG?=1

C_FILES=philosophers.c input_parser.c philo_builder.c philo_handler.c mutex_helper.c philo_utils.c
CFLAGS=-DMAX_PHILOSOPHERS='$(MAX_PHILOSOPHERS)' -DDEBUG='$(DEBUG)' -Wall -Werror -Wextra -pthread -g3 # REMOVE SANITIZE BEFORE EVALUATION

O_FILES=$(C_FILES:.c=.o)

all: $(NAME)
headermk:
	@printf "\n\e[1;31m> \e[1;36mMaking \e[1;34m$(NAME)\e[1;36m...\
	\n\n\e[0;35mCommands\e[1;30m:\n"
$(NAME): headermk $(O_FILES)
	@printf "\n\e[0;33m-\e[1;32m "
	@printf "\e[1;31m! ! ! ! ! ! REMOVE -g3 -fsanitize=address BEFORE EVALUATION ! ! ! ! ! !\n\e[1;32m"
	$(CC)$(C_FLAGS) $(O_FILES) -g3 -o $(EXEC_NAME)
	@printf "\n\033[0m"
clean:
	@printf "\n\e[1;31m> \e[1;36mRemoving \e[1;34m$(NAME)\e[1;36m's objects...\
	\e[1;30m\n\n"
	@printf "\e[0;33m-\e[1;32m "
	rm -rf $(O_FILES)
	@printf "\n\033[0m"
fclean:
	@printf "\n\e[1;31m> \e[1;36mRemoving \e[1;34m$(NAME)\e[1;36m...\
	\e[1;30m\n\n"
	@printf "\e[0;33m-\e[1;32m "
	rm -rf $(EXEC_NAME) $(O_FILES)
	@printf "\n\033[0m"
re: fclean $(NAME)
.PHONY: all clean fclean re