##
## Makefile for  in /home/mathias/Bureau/projet_epitech/synthèse/ADM_projTester_2016
## 
## Made by Mathias
## Login   <mathias.descoin@epitech.eu@epitech.net>
## 
## Started on  Wed Jun 21 18:41:03 2017 Mathias
## Last update Wed Jun 21 18:45:32 2017 Mathias
##

SRC	=	test.c

OBJ	=	$(SRC:.c=.o)

NAME	=	projTester

CFLAGS	+=	-Wall -Werror -Wextra -pedantic -Ofast -g3

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
