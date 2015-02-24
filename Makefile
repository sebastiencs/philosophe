##
## Makefile for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Tue Feb 24 01:54:11 2015 chapui_s
## Last update Tue Feb 24 01:56:38 2015 chapui_s
##

NAME		= philo

SRC		= philosophe.c

OBJ		= $(SRC:.c=.o)

CC		= gcc

RM		= rm -rf

CFLAGS		+= -lpthread

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
