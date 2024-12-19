##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## makefile
##

SRC	=	src/main.c	\
		src/usage.c	\
		src/whoami.c	\
		src/create_app.c	\
		src/cut_script.c	\
		src/init_tables.c	\
		src/exec_commands.c	\
		src/get_public_ip.c	\
		src/manage_user_input.c	\
		src/fundamental_funcs/cleanstr.c	\
		src/fundamental_funcs/my_strstr.c	\
		src/fundamental_funcs/my_strlen.c	\
		src/fundamental_funcs/my_str_to_word_array.c

OBJ	=	$(SRC:.c=.o)

NAME	=	devops

all:	$(NAME)

$(NAME)	:
	gcc -Iinclude -o $(NAME) $(SRC) -g3

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *~

fclean:	clean
	rm -f *vgcore*
	rm -f coding-style-reports.log
	rm -f $(NAME)

re:	fclean all
