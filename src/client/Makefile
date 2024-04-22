##
## EPITECH PROJECT, 2024
## B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
## File description:
## Makefile
##

EXEC_CLIENT = myteams_cli

LIB = -luuid -L../../libs/myteams

SRC_CLIENT = main.c \
             connexion.c \
             handle_server_input.c \
             handle_client.c \
             select.c \
			 is_white.c \
			 process_logged.c \
			 handle_protocol.c \
			 parse_user.c \
			 str_to_word_array.c \
			 array_to_string.c \
			 tokenize.c \
			 read_c.c \
			 remove_char.c \
			 response/response_initialisation.c \
			 response/response_login.c \
			 response/response_send.c \
			 response/response_user.c \
			 response/response_messages.c \

GCC_PARAM = -W -Wall -Wextra -g3

all: $(EXEC_CLIENT)

$(EXEC_CLIENT): $(SRC_CLIENT)
	@gcc $(GCC_PARAM) $(LIB) -o $@ $^ -lmyteams
	@mv myteams_cli ../../myteams_cli

clean:
	rm -f $(EXEC_CLIENT)
