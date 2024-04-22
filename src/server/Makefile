##
## EPITECH PROJECT, 2024
## B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
## File description:
## Makefile
##

EXEC_SERVER = myteams_server

LIB = -luuid -L../../libs/myteams

SRC_SERVER =	server.c \
            	my_utils.c \
            	str_to_word_array.c \
            	arr_func.c \
            	read_file.c \
            	bind_and_listen.c \
            	handle_connexion.c \
            	handle_client.c \
            	handle_command.c \
            	index.c \
            	quit.c \
            	file.c \
            	accept_connect.c \
            	msg.c \
            	database.c \
            	login.c \
            	tokenize.c \
            	verify_quoted.c \
            	print_sd_info.c \
            	set_socket.c \
				trim_input.c \
				is_whitespace.c \
				users.c \
				uuid.c \
				process_login.c \
				send_all.c \
				help.c \
				array_to_string.c \
				quotes.c \
				logout.c \
				cmd_user.c \
				messages.c \
				create.c \

GCC_PARAM = -W -Wall -Wextra -g3

all: $(EXEC_SERVER)

$(EXEC_SERVER): $(SRC_SERVER)
	@gcc $(GCC_PARAM) $(LIB) -o $@ $^ -lmyteams
	@mv myteams_server ../../myteams_server

clean:
	rm -f $(EXEC_SERVER)
