##
## Makefile for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Tue Feb 24 01:54:11 2015 chapui_s
## Last update Sun Mar  1 15:14:54 2015 chapui_s
##

NAME		= philo

SRC		= src/philosophe.c		\
		  src/manage_sdl.c		\
		  src/manage_config.c		\
		  src/disp.c			\
		  src/access_status.c		\
		  src/run_thread.c		\
		  src/init.c			\
		  src/destroy.c			\
		  src/manage_le_bordel.c

OBJ		= $(SRC:.c=.o)

CC		= gcc

RM		= rm -rf

override CFLAGS	+= -lpthread -lSDL -Wall -Wextra -L ./lib -I ./includes/

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
