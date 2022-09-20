# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/09/20 12:51:39 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c window.c image.c hooks.c maps.c utils.c display_image.c \
	pixies.c moves.c tools.c check.c colours.c colour_conversions.c \
	display.c

OBJS	= $(addprefix srcs/, ${SRCS:.c=.o})

FLAGS = -Wall -Wextra -Werror

LINKS = -lglfw -L /goinfre/faventur/.brew/Cellar/glfw/3.3.8/lib/

RM =	rm -f

NAME = so_long

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
	@gcc $(FLAGS) $(OBJS) $(LINKS) libft.a libmlx42.a -o $(NAME)
	@echo "$(CURSIVE)$(HIBLUE)Parce qu'ouvrir une fenêtre,$(NONE)"
	@echo "$(CURSIVE)$(HIGREEN)c'est surfait.$(NONE)"

.c.o:
	gcc -Wall -Wextra -Werror -c -I./MLX42/include/MLX42 -I./includes -I./libft/includes $< -o ${<:.c=.o}

exe: all
	@./$(NAME)

clean:
	@$(RM) libft.a $(OBJS)
	@$(MAKE) clean -C ./libft
	@$(MAKE) fclean -C ./MLX42

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./libft
	@$(MAKE) fclean -C ./MLX42

re: fclean all
