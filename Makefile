# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 13:47:31 by afonck            #+#    #+#              #
#    Updated: 2019/03/29 11:07:15 by sluetzen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc
FLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -O3
LIBRARIES = -lft -lSDL2 -L$(LIBFT_DIRECTORY) -L$(SDL2_LIB_DIRECTORY)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADER) -I$(SDL2_HEADERS_DIRECTORY)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADER = $(LIBFT_DIRECTORY)

SDL2 = $(SDL2_LIB_DIRECTORY)libSDL2.a
SDL2_LIB_DIRECTORY = ./sdl2_lib/
SDL2_HEADERS_DIRECTORY = ./sdl2_lib/SDL2_HEADERS/

HEADERS_LIST = 

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./src/
SOURCES_LIST = main.c 

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS) #$(SDL2)
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

#$(SDL2):
#	@echo "$(NAME): $(GREEN)Creating $(SDL2)...$(RESET)"
#	@$(MAKE) -sC $(SDL2_LIB_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	#@$(MAKE) -sC $(SDL2_LIB_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	#@rm -f $(SDL2)
	#@echo "$(NAME): $(RED)$(SDL2) was deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
