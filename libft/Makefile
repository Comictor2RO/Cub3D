# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggabor <ggabor@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 22:31:54 by ggabor            #+#    #+#              #
#    Updated: 2025/01/12 19:27:52 by ggabor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FUNC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_memcmp.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BFUNC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
        ft_lstclear.c ft_lstiter.c

OBJ = $(FUNC:.c=.o)
BOBJ = $(BFUNC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all:		$(NAME)
	
$(NAME): 	$(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "libft.a created"

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BOBJ)
	@echo "clean object"

fclean: clean 
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

bonus: $(OBJ) $(BOBJ)
	@ar rcs $(NAME) $(OBJ) $(BOBJ)	   	

re:		fclean all