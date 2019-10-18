# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <afonck@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 13:47:31 by afonck            #+#    #+#              #
#    Updated: 2019/10/18 13:35:17 by afonck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
DEBUG_NAME = wolf3d_debug

CC = clang

CFLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -O3
DEBUGFLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -g

LIBRARIES = -lft -lSDL2-2.0.0 -lSDL2_ttf-2.0.0 -L$(LIBFT_DIRECTORY) -L$(SDL2_LIB_DIRECTORY)lib -L$(SDL2TTF_LIB_DIRECTORY)lib
DEBUGLIBRARIES = -lft -lSDL2-2.0.0 -lSDL2_ttf-2.0.0 -L$(LIBFT_DIRECTORY) -L$(SDL2_LIB_DIRECTORY)lib -L$(SDL2TTF_LIB_DIRECTORY)lib
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADER) -I$(SDL2_HEADERS_DIRECTORY) -I$(SDL2TTF_HEADERS_DIRECTORY)

HARD_DBG ?= 1

CURRENT_DIR = $(shell pwd)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADER = $(LIBFT_DIRECTORY)

SDL2 = $(SDL2_LIB_DIRECTORY)lib/libSDL2.dylib
SDL2TTF = $(SDL2TTF_LIB_DIRECTORY)lib/libSDL2_ttf.dylib
SDL2_LIB_DIRECTORY = ./sdl2_lib/
SDL2TTF_LIB_DIRECTORY = ./sdl2_ttf_lib/
SDL2_HEADERS_DIRECTORY = ./SDL/include/
SDL2TTF_HEADERS_DIRECTORY = ./SDL_TTF/

HEADERS_LIST = wolf3d.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./src/
SOURCES_LIST = main.c \
	       find_wall_calculation.c \
	       free.c \
	       init_structs.c \
	       init.c \
	       movement.c \
	       multithreading.c \
	       raycasting.c \
		   texture.c \
		   parsing.c \
		   error_handling.c \
		   drawing.c \
		   checking.c \
		   handle_fps.c \
		   utils.c

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_DIRECTORY_DEBUG = objects_debug/

OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))
OBJECTS_DEBUG = $(addprefix $(OBJECTS_DIRECTORY_DEBUG), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re debug

all: $(NAME)

$(SDL2):
	@mkdir -p $(SDL2_LIB_DIRECTORY)/build && \
	cd $(SDL2_LIB_DIRECTORY)build && \
	$(CURRENT_DIR)/SDL/configure --prefix $(CURRENT_DIR)/$(SDL2_LIB_DIRECTORY) && \
	make && \
	make install

$(SDL2TTF):
	@export PATH=$(PATH):$(CURRENT_DIR)/$(SDL2_LIB_DIRECTORY)bin && \
	mkdir -p $(SDL2TTF_LIB_DIRECTORY)/build && \
	cd $(SDL2TTF_LIB_DIRECTORY)build && \
	$(CURRENT_DIR)/SDL_ttf/configure --prefix $(CURRENT_DIR)/$(SDL2TTF_LIB_DIRECTORY) && \
	make && \
	make install

$(NAME): $(SDL2) $(SDL2TTF) $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY_DEBUG):
	@mkdir -p $(OBJECTS_DIRECTORY_DEBUG)
	@echo "$(DEBUG_NAME): $(GREEN)$(OBJECTS_DIRECTORY_DEBUG) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(OBJECTS_DIRECTORY_DEBUG)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
ifeq ($(HARD_DBG), 1)
	@$(eval DEBUGFLAGS += -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined)
	@$(eval DEBUGLIBRARIES += -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined)
endif

	@$(CC) $(DEBUGFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@rm -rf $(SDL2_LIB_DIRECTORY)build
	@rm -rf $(SDL2TTF_LIB_DIRECTORY)build
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2TTF_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)SDL2 and SDL2TTF object files were deleted$(RESET)"

fclean: clean
	@rm -rf $(SDL2_LIB_DIRECTORY)
	@rm -rf $(SDL2TTF_LIB_DIRECTORY)
	@echo "$(NAME): $(RED)SDL2 and SDL2TTF was deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

debug: $(DEBUG_NAME)

$(DEBUG_NAME): $(SDL2) $(SDL2TTF) $(LIBFT) $(OBJECTS_DIRECTORY_DEBUG) $(OBJECTS_DEBUG)
	@$(CC) $(DEBUGLIBRARIES) $(INCLUDES) $(OBJECTS_DEBUG) -o $(DEBUG_NAME)
	@echo "\n$(DEBUG_NAME): $(GREEN)object debug files were created$(RESET)"
	@echo "$(DEBUG_NAME): $(GREEN)$(DEBUG_NAME) was created$(RESET)"

debugclean:
	@rm -rf $(OBJECTS_DIRECTORY_DEBUG)
	@echo "$(DEBUG_NAME): $(RED)$(OBJECTS_DIRECTORY_DEBUG) was deleted$(RESET)"
	@echo "$(DEBUG_NAME): $(RED)debug objects files were deleted$(RESET)"

debugfclean: debugclean
	@rm -f $(DEBUG_NAME)
	@echo "$(DEBUG_NAME): $(RED)$(DEBUG_NAME) was deleted$(RESET)"

debugre:
	@$(MAKE) debugfclean
	@$(MAKE) debug

