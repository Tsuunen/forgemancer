NAME = forgemancer
CC = gcc
CFLAGS = `pkg-config --cflags gtk4` -Iincludes -g3
LIBS = `pkg-config --libs gtk4` -lmysqlclient   
SRC = src/main.c\
	  src/database_handler/database_utils.c\
	  src/database_handler/get_user.c\
	  src/database_handler/add_user.c\
	  src/database_handler/get_all_uuids.c\
	  src/utils/dotenv_load.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

