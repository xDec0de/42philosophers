# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 10:51:01 by danimart          #+#    #+#              #
#    Updated: 2025/07/01 17:31:05 by daniema3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MAX_PHILOSOPHERS?=200

SRC_DIR = ./src
OBJ_DIR = ./objs
H_DIR = ./headers

CC = gcc
CFLAGS =	-Wall -Werror -Wextra \
			-pthread \
			-g3 \
			-fdiagnostics-color=always \
			-DMAX_PHILOSOPHERS='$(MAX_PHILOSOPHERS)' \
			-I$(H_DIR)

SRCS =	philosophers.c \
		input_parser.c \
		philo_builder.c \
		philo_handler.c \
		mutex_helper.c \
		philo_utils.c

RED = \e[0;31m
BRED = \e[1;31m
GREEN = \e[1;32m
YLW = \e[0;33m
BYLW = \e[1;33m
BLUE = \e[1;36m
GRAY = \e[0;30m
RES = \e[0m                                                                   

WNAME = $(BYLW)$(NAME)$(YLW)
OKNAME = $(BLUE)$(NAME)$(GREEN)

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo -n "\r⏳ $(YLW)Compiling $(notdir $<)$(GRAY)...$(RES)"
	@{\
		ERR=$$( ($(CC) $(CFLAGS) -c $< -o $@) 2>&1 );\
		if [ $$? -ne 0 ]; then\
			echo -n "\r❌ $(RED)Failed to compile $(BRED)$(notdir $<)";\
			echo -n "$(GRAY):$(RES)";\
			echo "\n$$ERR";\
			exit 1;\
		fi;\
	}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -n "\r✅ $(OKNAME) $(GREEN)successfully compiled!$(RES)"
	@echo 

clean:
	@echo -n "\r⏳ $(YLW)Removing $(WNAME) objs$(GRAY)...$(RES)"
	@rm -rf $(OBJ_DIR)
	@echo -n "\r✅ $(GREEN)Removed $(OKNAME) objs$(GRAY).$(RES)"
	@echo 

fclean: clean
	@echo -n "\r⏳ $(YLW)Removing $(WNAME) executable$(GRAY)...$(RES)"
	@rm -rf $(NAME)
	@echo -n "\r✅ $(GREEN)Removed $(OKNAME) executable\$(GRAY).$(RES)"
	@echo 

re: fclean $(NAME)

.PHONY: all clean fclean re
