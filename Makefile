NAME				= monitoring

LIBFT_PATH			= libft
LIBFT				= $(LIBFT_PATH)/libft.a

SOURCE_PATH			= sources
SOURCE_FILES		= main.c

HEADER_PATH			= include
HEADER_FILES		= monitoring.h

OBJECT_PATH			= objects
OBJECT_FILES		= $(SOURCE_FILES:%.c=$(OBJECT_PATH)/%.o)

CC					= cc
CFLAGS				= -g3 -Wall -Wextra -Werror
# LDFLAGS				=
REMOVE				= rm -rf

vpath				%.c $(SOURCE_PATH)
vpath				%.h $(HEADER_PATH)

all:				$(NAME)

run:				all
					./monitoring

vg:					all
					valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./monitoring

$(NAME):			$(OBJECT_FILES) $(OBJECT_PATH) $(LIBFT)
					$(CC) $(CFLAGS) $(OBJECT_FILES) $(LIBFT) -o $@

$(OBJECT_PATH)/%.o:	%.c $(HEADER_FILES) Makefile | $(OBJECT_PATH)
					$(CC) $(CFLAGS) -I $(HEADER_PATH) -c $< -o $@

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
