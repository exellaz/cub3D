# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: we <we@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 14:09:15 by tjun-yu           #+#    #+#              #
#    Updated: 2024/05/10 12:35:21 by we               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Flags
CFLAGS = -Wall -Wextra -Werror

# Directories
OBJ_DIR = ../obj/

#Sources & targets
SOURCES =	ft_atoi.c ft_atoi_base.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c\
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_pow.c ft_putchar_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c\
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c\
			ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c\
			ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)
BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstdelone.c ft_lstiter.c ft_lstclear.c ft_lstmap.c
BONUS_OBJS = $(BONUS:%.c=$(OBJ_DIR)%.o)
INCLUDE = libft.h
NAME = libft.a

#Rules & recipes
all : $(NAME)

$(NAME) : $(OBJECTS)
	ar rcs $@ $^
	ranlib $@

bonus: $(OBJECTS) $(BONUS_OBJS)
	ar rcs $(NAME) $^
	ranlib $(NAME)

obj : $(OBJECTS) $(BONUS_OBJS)

$(OBJ_DIR)%.o : %.c $(INCLUDE)
	cc $(CFLAGS) -c -I.$(INCLUDE) $< -o $@

clean :
	rm -f $(OBJECTS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re