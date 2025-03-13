# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: we <we@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 14:09:15 by tjun-yu           #+#    #+#              #
#    Updated: 2025/03/14 00:44:44 by we               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Flags
CFLAGS = -Wall -Wextra -Werror

# Directories
OBJ_DIR = ../obj

#Sources & targets
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)
HEADER = libft.h ../libmem/libmem.h
INCLUDE = -I. -I../libmem
NAME = libft.a

#Rules & recipes
all : $(NAME)

$(NAME) : $(OBJECTS)
	ar rcs $@ $^
	ranlib $@

obj : $(OBJECTS)

$(OBJ_DIR)/%.o : %.c $(HEADER)
	cc $(CFLAGS) -c $(INCLUDE) $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
