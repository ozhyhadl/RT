# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/02 15:43:48 by apavlov           #+#    #+#              #
#    Updated: 2019/09/14 18:19:48 by apavlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS =  -Wall -Wextra #-g -fsanitize=address #-Werror

NAME = RT

SRC =	main.c init_cl.c init_sdl.c output.c parser.c render.c user_event.c \
		math.c init.c mouse_events.c\
		xml/xml_read.c xml/xml_create_obj.c xml/xml_add_param.c \
		xml/xml_add_param_help.c xml/xml_add_light.c xml/xml_create_cam.c xml/xml_it_is.c \
		xml/xml_save.c xml/xml_write_obj.c xml/xml_write_other.c xml/xml_write_param.c

HEADERS = rt.h parse.h terminal_colors.h mymath.h editor.h

INC_DIR = ./includes/

INC = $(addprefix $(INC_DIR), $(HEADERS))

SRC_DIR = ./src/

OBJ_DIR = ./obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FT = ./libft/

MXML = ./frameworks/mxml-3.0/lib #add folder path ++

FT_LIB	= $(addprefix $(FT),libft.a)

LINKS = -L$(FT) -l ft -lm #add link mxml ++
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LINKS += -lSDL2 -lSDL2_image -lOpenCL -lmxml -lpthread
else
	LINKS += -L$(MXML) -lmxml
endif
SDL_PATH = ./framework

INCLUDES = 		-I$(FT) -I$(INC_DIR) -I./frameworks/mxml-3.0/include

ifeq ($(UNAME_S),Darwin)
INCLUDES += -I./frameworks/SDL2.framework/Headers \
			-I./frameworks/SDL2_image.framework/Headers \
			-F./frameworks 
endif

				

FRAMEWORKS :=
ifeq ($(UNAME_S),Darwin)
FRAMEWORKS += 	-F./frameworks \
				-rpath ./frameworks \
				-framework AppKit -framework OpenGL \
				-framework SDL2 -framework SDL2_image \
				-framework OpenCL
endif

all: obj_dir $(FT_LIB) $(NAME)
	echo 'Compilated!'

obj_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/xml

xml:
	/lib/mxml-3.0

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FRAMEWORKS) $(OBJ) -o $(NAME) $(LINKS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all
