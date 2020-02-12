# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 13:47:31 by afonck            #+#    #+#              #
#    Updated: 2020/02/12 11:11:21 by phaydont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom_nukem
DEBUG_NAME = doom_nukem_debug

CC = clang

CFLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -O3
DEBUGFLAGS = -Wall -Werror -Wextra -D_THREAD_SAFE -g

LDFLAGS = -L$(LIBFT_DIRECTORY) -L$(LIBBMP_DIRECTORY) -L$(SDL2_LIB_DIRECTORY)lib -L$(SDL2TTF_LIB_DIRECTORY)lib -L$(OPENAL_LIB_DIRECTORY)lib
LDLIBS = -lft -lbmp -lSDL2 -lSDL2_ttf -lopenal

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADER) -I$(LIBBMP_HEADER) -I$(SDL2_HEADERS_DIRECTORY) -I$(SDL2TTF_HEADERS_DIRECTORY) -I$(OPENAL_HEADERS_DIRECTORY)
HARD_DBG ?= 1

CURRENT_DIR = $(shell pwd)
ASSETS_DIR = ./assets/
ASSETS_ARCHIVE = assets.tar.gz

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

OPENAL = $(OPENAL_LIB_DIRECTORY)lib/libopenal.dylib
OPENAL_VERSION = 1.20.1

SDL2_LIB_DIRECTORY = ./sdl2_lib/
SDL2TTF_LIB_DIRECTORY = ./sdl2_ttf_lib/
OPENAL_LIB_DIRECTORY = ./openal-soft-lib/

SDL2_HEADERS_DIRECTORY = $(SDL2_LIB_DIRECTORY)include/SDL2/
SDL2TTF_HEADERS_DIRECTORY = $(SDL2TTF_LIB_DIRECTORY)include/SDL2/
OPENAL_HEADERS_DIRECTORY = $(OPENAL_LIB_DIRECTORY)include/AL/

HEADERS_LIST = doom.h \
			libwav.h

HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./src/
SOURCES_LIST = main.c \
			game.c \
			game_blit_hud.c \
			game_create_surfaces.c \
			init.c \
			init_structs.c \
			init_wall_textures.c \
			null_pointers.c \
			free.c \
			free_sound_and_ttf.c \
			drawing.c \
			draw_line.c \
			fixed_minimap.c \
			rot_minimap.c \
			perspective_view.c \
			vector.c \
			vector_mult_div.c \
			vector_transform.c \
			vector_multiplications.c \
			vector_create_reset.c \
			poll_event.c \
			poll_event_checks.c \
			handle_keys.c \
			movement.c \
			movement_collisions.c \
			movement_surroundings.c \
			menu.c \
			menu_init.c \
			menu_options.c \
			text.c \
			sdl_subfunctions.c \
			ll_sector.c \
			ll_sector2.c \
			ll_sector3.c \
			ll_wall.c \
			ll_wall2.c\
			editor.c \
			mouse.c \
			editor_menu.c \
			editor_main_surfaces.c\
			editor_check.c \
			editor_blit.c \
			editor_create_walls.c \
			new_blit.c \
			map.c \
			map_reader_main.c \
			map_reader_sectors.c \
			map_writer_main.c \
			map_writer_sectors.c \
			editor_events.c \
			wav_parse.c \
			texture_mapping.c \
			editor_events_mouse.c \
			editor_events_keys.c \
			editor_events_keys_a_to_l.c \
			editor_events_keys_m_to_q.c \
			editor_events_keys_r_to_u.c \
			editor_mouse_collide1.c \
			editor_mouse_collide2.c \
			mouse_movement.c \
			sound.c \
			sound_init.c \
			music.c \
			openal_sub_functions.c \
			end_level_loops.c \
			error.c \
			editor_null_pointers.c \
			editor_create_surfaces.c \
			editor_init_options.c \
			editor_init_instructs.c \
			editor_init.c \
			editor_events_height_input.c \
			editor_free.c \
			editor_blit_alerts.c \
			editor_drawing.c \
			editor_blit_options.c \
			enemy.c \
			enemy_actions.c \
			enemy_anim.c \
			player.c \
			player_attack.c \
			player_blit.c \
			floor_ceiling.c

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

$(OPENAL):
	curl -Ol https://kcat.strangesoft.net/openal-releases/openal-soft-1.20.1.tar.bz2 && \
	tar -xvf openal-soft-$(OPENAL_VERSION).tar.bz2 && \
	rm openal-soft-$(OPENAL_VERSION).tar.bz2 && \
	mkdir -p $(OPENAL_LIB_DIRECTORY)/build && \
	cd $(OPENAL_LIB_DIRECTORY)build && \
	cmake -DCMAKE_INSTALL_PREFIX:PATH=$(CURRENT_DIR)/$(OPENAL_LIB_DIRECTORY) $(CURRENT_DIR)/openal-soft-$(OPENAL_VERSION) && \
	make && \
	make install && \
	cd ../..
	rm -rf openal-soft-$(OPENAL_VERSION)

$(ASSETS_DIR): $(ASSETS_ARCHIVE)
	tar -xzvf $(ASSETS_ARCHIVE)

$(NAME): $(SDL2) $(SDL2TTF) $(OPENAL) $(LIBFT) $(LIBBMP) $(OBJECTS_DIRECTORY) $(OBJECTS) $(ASSETS_DIR)
	@$(CC) $(INCLUDES) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"
	@install_name_tool -change @rpath/libopenal.1.dylib $(OPENAL_LIB_DIRECTORY)lib/libopenal.dylib $(NAME)

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
	@rm -rf $(OPENAL_LIB_DIRECTORY)build
	@echo "$(NAME): $(RED)$(LIBFT_DIRECTORY) and $(LIBBMP_DIRECTORY) were cleaned$(RESET)"
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)$(SDL2TTF_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)$(OPENAL_LIB_DIRECTORY)build was deleted$(RESET)"
	@echo "$(NAME): $(RED)SDL2 and SDL2TTF object files were deleted$(RESET)"

fclean: clean
	@rm -rf $(SDL2_LIB_DIRECTORY)
	@rm -rf $(SDL2TTF_LIB_DIRECTORY)
	@rm -rf $(OPENAL_LIB_DIRECTORY)
	@rm -rf $(ASSETS_DIR)
	@echo "$(NAME): $(RED)SDL2 and SDL2TTF was deleted$(RESET)"
	@echo "$(NAME): $(RED)OPENAL was deleted$(RESET)"
	@echo "$(NAME): $(RED)assets folder was deleted$(RESET)"
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

$(DEBUG_NAME): $(SDL2) $(SDL2TTF) $(OPENAL) $(LIBFT) $(LIBBMP) $(OBJECTS_DIRECTORY_DEBUG) $(OBJECTS_DEBUG) $(ASSETS_DIR)
	@$(CC) $(INCLUDES) $(OBJECTS_DEBUG) $(LDFLAGS) $(LDLIBS) -o $(DEBUG_NAME)
	@echo "\n$(DEBUG_NAME): $(GREEN)object debug files were created$(RESET)"
	@echo "$(DEBUG_NAME): $(GREEN)$(DEBUG_NAME) was created$(RESET)"
	@install_name_tool -change @rpath/libopenal.1.dylib $(OPENAL_LIB_DIRECTORY)lib/libopenal.dylib $(DEBUG_NAME)

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

