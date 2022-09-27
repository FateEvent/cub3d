# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/09/27 10:18:56 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

ARGS = map.ber

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

LINKS = -lglfw -L /goinfre/faventur/.brew/Cellar/glfw/3.3.8/lib/

LIBLINKS = -I./MLX42/include/MLX42 -I./includes -I./libft/includes

SRC_PATH = srcs/

OBJ_PATH = bin/

C_EXTENSION = .c

SRCS_FILES = main window hooks maps utils display pixies moves tools \
		check colours colour_conversions useless_tools ray_casting_tools

OBJS	= $(addprefix srcs/, ${SRCS:.c=.o})

RM =	rm -f

SRCS_FILES_EXT 		+= 	$(addsuffix $(C_EXTENSION), $(SRCS_FILES))

SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))

OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:c=o))

NONE = \033[0m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC ./libft
	@$(MAKE) -sC ./MLX42
	@mv ./libft/libft.a .
	@mv ./MLX42/libmlx42.a .
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) libft.a libmlx42.a $(LINKS) -fsanitize=address
	@echo "$(CURSIVE)$(HIBLUE)Parce qu'ouvrir une fenêtre,$(NONE)"
	@echo "$(CURSIVE)$(HIGREEN)c'est surfait.$(NONE)"

.c.o:
	@$(CC) $(FLAGS) -c $(LIBLINKS) $< -o ${<:.c=.o}

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} ${LIBLINKS} -c $< -o $@

exe: all
	@./$(NAME) $(ARGS)

clean:
	@$(RM) -r libft.a libmlx42.a $(OBJ_PATH)
	@$(MAKE) clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

relib: fclean
	@$(MAKE) re -sC ./MLX42
	@$(MAKE) all

.PHONY: all exe clean fclean re