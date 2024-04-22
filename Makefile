##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## myteams
##

NAME = myteams

all:
	@cd src/client/ && make
	@cd src/server/ && make

W_FLAG = -W -Wall -Wextra -g3

LAST_FLAG = -Werror -ansi -pedantic

FLAG_VAL = --tool=memcheck --leak-check=yes --show-reachable=yes

FLAG_VAL2 = --leak-check=full --show-leak-kinds=all --track-origins=yes -s

val: $(NAME)
	valgrind ./$(NAME)

push:	fclean
	git add .
	echo git commit -m ""
	echo git push

clean:
		rm -f coding-style-reports.log

fclean: clean
		rm -f myteams_cli
		rm -f myteams_server
		rm -rf ./database/*

re:		fclean all

.PHONY:	all fclean clean re
