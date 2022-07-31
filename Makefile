NAME				:= monitoring

LIBFT_PATH			:= libft
LIBFT				:= $(LIBFT_PATH)/libft.a

SOURCE_PATH			:= sources
SOURCE_FILES		:= main.c utils.c protocol_node.c parsing.c

HEADER_PATH			:= include
HEADER_FILES		:= monitoring.h

OBJECT_PATH			:= objects
OBJECT_FILES		:= $(SOURCE_FILES:%.c=$(OBJECT_PATH)/%.o)

CC					:= cc
CFLAGS				:= -g3 -Wall -Wextra #-Werror
LDFLAGS				:= -L $(LIBFT_PATH) -lft
IFLAGS				:= -I $(HEADER_PATH)
REMOVE				:= rm -rf
VALGRIND			:= valgrind
VGFLAGS				:= --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

vpath				%.c $(SOURCE_PATH)
vpath				%.h $(HEADER_PATH)

all:				$(NAME)

run:				all
					./${NAME}

vg:					all
					$(VALGRIND) $(VGFLAGS) ./${NAME}

test:				all
					cd tests && sh tester.sh

$(NAME):			$(OBJECT_FILES) $(OBJECT_PATH) $(LIBFT)
					$(CC) $(CFLAGS) -o $@ $(OBJECT_FILES) $(LDFLAGS)

$(OBJECT_PATH)/%.o:	%.c $(HEADER_FILES) Makefile | $(OBJECT_PATH)
					$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJECT_PATH):
					mkdir -p $@

$(LIBFT):
					$(MAKE) -C $(LIBFT_PATH)

clean:
					$(MAKE) -C $(LIBFT_PATH) clean
					$(REMOVE) $(OBJECT_PATH)

fclean:				clean
					$(MAKE) -C $(LIBFT_PATH) fclean
					$(REMOVE) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re run vg
