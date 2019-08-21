# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 18:55:30 by afonck            #+#    #+#              #
#    Updated: 2018/12/20 19:38:35 by afonck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

INCLUDES = -I$(PRINTF_INC_DIR) -I./

PRINTF_DIR	= ./ft_printf/
PRINTF_SRC_DIR	= ./ft_printf/src/
PRINTF_INC_DIR	= ./ft_printf/includes/
PRINTF_OBJ_DIR	= ./ft_printf/obj/
PRINTF_SRC_LIST	= ft_printf.c \
		  float.c \
		  percent.c \
		  char.c \
		  string.c \
		  int.c \
		  uint.c \
		  bin.c \
		  octal.c \
		  hex.c \
		  hexcap.c \
		  pointer.c \
		  checklen.c \
		  flags.c \
		  pad.c \
		  float_spec.c \
		  bonus.c \
		  lmod.c \
		  utils.c

PRINTF_OBJ_LIST = $(PRINTF_SRC_LIST:.c=.o)

PRINTF_SRC = $(addprefix $(PRINTF_SRC_DIR), $(PRINTF_SRC_LIST))
PRINTF_OBJ = $(addprefix $(PRINTF_OBJ_DIR), $(PRINTF_OBJ_LIST))

CFLAGS	= -Wall -Werror -Wextra

FILES		= $(shell ls | grep -E "ft_.+\.c") \
		get_next_line.c

OBJ			= $(FILES:%.c=%.o)

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ) $(PRINTF_OBJ_DIR) $(PRINTF_OBJ)
	@ar rcs $(NAME) $(OBJ) $(PRINTF_OBJ)

$(OBJ): $(FILES) libft.h
	@gcc $(CFLAGS) $(INCLUDES) -c $(FILES)

$(PRINTF_OBJ_DIR):
	@mkdir -p $(PRINTF_OBJ_DIR)

$(PRINTF_OBJ_DIR)%.o: $(PRINTF_SRC_DIR)%.c $(PRINTF_INC_DIR)ft_printf.h
	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ) $(PRINTF_OBJ)
	@rm -rf $(PRINTF_OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
