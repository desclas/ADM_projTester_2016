##
## Makefile for  in /home/mathias/Bureau/projet_epitech/synthèse/ADM_projTester_2016
## 
## Made by Mathias
## Login   <mathias.descoin@epitech.eu@epitech.net>
## 
## Started on  Wed Jun 21 18:41:03 2017 Mathias
## Last update Sat Jun 24 14:11:50 2017 Mathias
##

SRC	=	src/main.c		\
		src/get.c		\
		src/print.c		\
		src/utilities.c		\
		src/all_exec.c		\
		src/print_exec.c

OBJ	=	$(SRC:.c=.o)

NAME	=	projTester

CFLAGS	+=	-Iinclude -Wall -Werror -Wextra -pedantic -g3

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
