# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdincbud <sdincbudstudent.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 18:42:02 by maabou-h          #+#    #+#              #
#    Updated: 2019/06/24 10:20:53 by maabou-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

SRC_PATH = srcs

SRC_NAME = 	pipes.c rooms.c init.c main.c parse.c print.c queue.c\
			solve.c tools.c path.c draw.c tools2.c tools3.c\
			img.c murphy.c murphy_helper.c murphy_helper2.c\
			bren.c visu.c tools4.c tools5.c tools6.c visu2.c

NAME = lem-in

LDFLAGS = -L./libft/

LDLIBS = -lft

CC = clang

CFLAGS = -I./includes -I./libft/includes -I./mlx/ -Werror -Wall -Wextra

MLX_FLAGS =  -lmlx -framework OpenGl -framework AppKit

OBJ_PATH = .obj

OBJ_NAME = $(SRC_NAME:%.c=%.o)
	OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
	SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

all: makelib $(NAME)

makelib :
	@printf "$(GREEN)Creating lib files$(NOC)\n"
	@make -C libft
	# @make -C mlx

$(NAME): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(MLX_FLAGS)
	@printf "$(GREEN)Project successfully compiled$(NOC)"

$(OBJ): includes/lem_in.h libft/includes/libft.h libft/libft.a libft/includes/ft_colors.h libft/includes/ft_printf.h

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]\r"

norm:
	make norm -C libft && sleep 1 && clear
	norminette $(SRC) includes/lem_in.h

clean:
	@printf "$(RED)Supressing libraries files$(CYAN)\n"
	@make clean -C libft
	@make clean -C mlx
	@rm -rfv $(OBJ_PATH)

fclean: clean
	@make fclean -C libft
	@rm -fv $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
