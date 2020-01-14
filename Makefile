# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 13:47:31 by afonck            #+#    #+#              #
#    Updated: 2020/01/14 15:15:31 by sluetzen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom
DEBUG_NAME = doom_debug

CC = clang

CFLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -O3
DEBUGFLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -g

LDFLAGS = -L$(LIBFT_DIRECTORY) -L$(LIBBMP_DIRECTORY) -L$(SDL2_LIB_DIRECTORY)lib -L$(SDL2TTF_LIB_DIRECTORY)lib -L$(SDL2MIXER_LIB_DIRECTORY)lib
LDLIBS = -lft -lbmp -lSDL2 -lSDL2_ttf -lSDL2_mixer

INCLUDES =  -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADER) -I$(LIBBMP_HEADER) -I$(SDL2_HEADERS_DIRECTORY) -I$(SDL2TTF_HEADERS_DIRECTORY) -I$(SDL2MIXER_HEADERS_DIRECTORY)

HARD_DBG ?= 1

CURRENT_DIR = $(shell pwd)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADER = $(LIBFT_DIRECTORY)

LIBBMP = $(LIBBMP_DIRECTORY)libbmp.a
LIBBMP_DIRECTORY = ./libbmp/
LIBBMP_HEADER = $(LIBBMP_DIRECTORY)includes/

SDL2 = $(SDL2_LIB_DIRECTORY)lib/libSDL2.dylib
SDL2_VERSION = 2.0.10

SDL2TTF = $(SDL2TTF_LIB_DIRECTORY)lib/libSDL2_ttf.dylib
SDL2TTF_VERSION = 2.0.15

SDL2MIXER = $(SDL2MIXER_LIB_DIRECTORY)lib/libSDL2_mixer.dylib
SDL2MIXER_VERSION = 2.0.4

SDL2_LIB_DIRECTORY = ./sdl2_lib/
SDL2TTF_LIB_DIRECTORY = ./sdl2_ttf_lib/
SDL2MIXER_LIB_DIRECTORY = ./sdl2_mixer_lib/

SDL2_HEADERS_DIRECTORY = $(SDL2_LIB_DIRECTORY)include/SDL2/
SDL2TTF_HEADERS_DIRECTORY = $(SDL2TTF_LIB_DIRECTORY)include/SDL2/
SDL2MIXER_HEADERS_DIRECTORY = $(SDL2MIXER_LIB_DIRECTORY)include/SDL2/

HEADERS_LIST = doom.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./src/
SOURCES_LIST = main.c \
			init.c \
			init_structs.c \
			null_pointers.c \
			free.c \
			drawing.c \
			draw_line.c \
			fixed_minimap.c \
			rot_minimap.c \
			perspective_view.c \
			vector.c \
			map_parser.c \
			poll_event.c \
			handle_keys.c \
			movement.c \
			menu.c \
			text.c \
			SDL_sub_functions.c \
			ll_sector.c \
			ll_wall.c \
			editor.c \
			mouse.c \
			editor_menu.c \
			debug.c \
			create_surfaces.c\
			editor_check.c #\
	       multithreading.c \
		   texture.c \
		   parsing.c \
		   error_handling.c \
		   drawing.c \
		   checking.c \
		   handle_fps.c \
		   utils.c \
		   floor_and_ceiling.c

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
	curl -OL http://www.libsdl.org/release/SDL2-$(SDL2_VERSION).tar.gz && \
	tar -xvf SDL2-$(SDL2_VERSION).tar.gz && \
	rm SDL2-$(SDL2_VERSION).tar.gz && \
	mkdir -p $(SDL2_LIB_DIRECTORY)/build && \
	cd $(SDL2_LIB_DIRECTORY)build && \
	$(CURRENT_DIR)/SDL2-$(SDL2_VERSION)/configure --prefix $(CURRENT_DIR)/$(SDL2_LIB_DIRECTORY) && \
	make && \
	make install && \
	cd ../.. && \
	rm -rf SDL2-$(SDL2_VERSION);

$(SDL2TTF):
	curl -OL http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-$(SDL2TTF_VERSION).tar.gz && \
	tar -xvf SDL2_ttf-$(SDL2TTF_VERSION).tar.gz && \
	rm SDL2_ttf-$(SDL2TTF_VERSION).tar.gz && \
	export PATH="$(PATH):$(CURRENT_DIR)/$(SDL2_LIB_DIRECTORY)bin" && \
	mkdir -p $(SDL2TTF_LIB_DIRECTORY)/build && \
	cd $(SDL2TTF_LIB_DIRECTORY)build && \
	$(CURRENT_DIR)/SDL2_ttf-$(SDL2TTF_VERSION)/configure --prefix $(CURRENT_DIR)/$(SDL2TTF_LIB_DIRECTORY) && \
	make && \
	make install && \
	cd ../.. && \
	rm -rf SDL2_ttf-$(SDL2TTF_VERSION);

$(SDL2MIXER):
	curl -OL http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-$(SDL2MIXER_VERSION).tar.gz && \
	tar -xvf SDL2_mixer-$(SDL2MIXER_VERSION).tar.gz && \
	rm SDL2_mixer-$(SDL2MIXER_VERSION).tar.gz && \
	export PATH="$(PATH):$(CURRENT_DIR)/$(SDL2_LIB_DIRECTORY)bin" && \
	mkdir -p $(SDL2MIXER_LIB_DIRECTORY)/build && \
	cd $(SDL2MIXER_LIB_DIRECTORY)build && \
	$(CURRENT_DIR)/SDL2_mixer-$(SDL2MIXER_VERSION)/configure --prefix $(CURRENT_DIR)/$(SDL2MIXER_LIB_DIRECTORY) && \
	make && \
	make install && \
	cd ../.. && \
	rm -rf SDL2_mixer-$(SDL2MIXER_VERSION);

$(NAME): $(SDL2) $(SDL2TTF) $(SDL2MIXER) $(LIBFT) $(LIBBMP) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(CC) $(INCLUDES) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
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
	@$(eval LDFLAGS += -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined)
endif

	@$(CC) $(DEBUGFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(LIBBMP):
	@echo "$(NAME): $(GREEN)Creating $(LIBBMP)...$(RESET)"
	@$(MAKE) -sC $(LIBBMP_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(LIBBMP_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@rm -rf $(SDL2_LIB_DIRECTORY)build
	@rm -rf $(SDL2TTF_LIB_DIRECTORY)build
	@rm -rf $(SDL2MIXER_LIB_DIRECTORY)build
	@echo "$(NAME): $(RED)$(LIBFT_DIRECTORY) and $(LIBBMP_DIRECTORY) were cleaned$(RESET)"
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2TTF_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2MIXER_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)SDL2 and SDL2TTF object files were deleted$(RESET)"

fclean: clean
	@rm -rf $(SDL2_LIB_DIRECTORY)
	@rm -rf $(SDL2TTF_LIB_DIRECTORY)
	@rm -rf $(SDL2MIXER_LIB_DIRECTORY)
	@echo "$(NAME): $(RED)SDL2 and SDL2TTF was deleted$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@$(MAKE) -sC $(LIBBMP_DIRECTORY) fclean
	@echo "$(NAME): $(RED)$(LIBBMP) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

debug: $(DEBUG_NAME)

$(DEBUG_NAME): $(SDL2) $(SDL2TTF) $(SDL2MIXER) $(LIBFT) $(LIBBMP) $(OBJECTS_DIRECTORY_DEBUG) $(OBJECTS_DEBUG)
	@$(CC) $(INCLUDES) $(OBJECTS_DEBUG) $(LDFLAGS) $(LDLIBS) -o $(DEBUG_NAME)
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

