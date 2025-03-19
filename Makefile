# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 10:51:01 by danimart          #+#    #+#              #
#    Updated: 2025/03/19 18:19:39 by daniema3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -DMAX_PHILOSOPHERS='$(MAX_PHILOSOPHERS)' -Wall \
-Werror -Wextra -pthread -g3 -fdiagnostics-color=always

SRC_DIR = ./src
OBJ_DIR = ./objs

MAX_PHILOSOPHERS?=200

# > ~ List utilities

SRCS =	philosophers.c\
		input_parser.c\
		philo_builder.c\
		philo_handler.c\
		mutex_helper.c\
		philo_utils.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo -n "\r⏳ \e[0;33mCompiling $(notdir $<)\e[0m                          "
	@{\
		ERR=$$( ($(CC) $(CFLAGS) -c $< -o $@) 2>&1 );\
		if [ $$? -ne 0 ]; then\
			echo -n "\r❌ \e[0;31mFailed to compile $(notdir $<):        \e[0m";\
			echo "\n$$ERR";\
			exit 1;\
		fi;\
	}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -n "\r✅ \e[1;36m$(NAME) \e[0;32msuccessfully compiled!               "
	@echo 

clean:
	@echo -n "\r⏳ \e[0;33mRemoving $(NAME) objs.                               "
	@rm -rf $(OBJ_DIR)
	@echo -n "\r✅ \e[0;32mSuccessfully removed $(NAME) objs.                   "
	@echo 

fclean: clean
	@echo -n "\r⏳ \e[0;33mRemoving $(NAME) executable.                         "
	@rm -rf $(NAME)
	@echo -n "\r✅ \e[0;32mSuccessfully removed $(NAME) executable.             "
	@echo 

re: fclean $(NAME)

.PHONY: all clean fclean re
