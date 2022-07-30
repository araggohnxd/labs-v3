NAME				= libft.a
SO					= $(NAME:.a=.so)

HEADER				= libft.h

SOURCE_PATH			= sources
SOURCE_FILES		= ft_atoi.c ft_calloc.c ft_bzero.c ft_isalnum.c \
					ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
					ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
					ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
					ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c \
					ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_itoa_base.c \
					ft_gnl.c ft_gnl_multifd.c ft_printf.c ft_printf_handlers.c \
					ft_strjoin_free.c ft_free_matrix.c ft_isspace.c \
					ft_strnlen.c ft_memfree.c ft_utoa.c ft_atoll.c ft_strcmp.c \
					ft_skip_chars.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
					ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
					ft_lstiter.c ft_lstmap.c ft_strtrim_free.c

OBJECT_PATH			= objects
OBJECT_FILES		= $(SOURCE_FILES:%.c=$(OBJECT_PATH)/%.o)

vpath				%.c $(SOURCE_PATH)

CC					= cc
CFLAGS				= -g3 -Wall -Wextra -Werror
REMOVE				= rm -rf

all:				$(NAME)

$(NAME):			$(OBJECT_FILES) $(OBJECT_PATH)
					ar -rcs $(NAME) $(OBJECT_FILES)

$(OBJECT_PATH)/%.o:	%.c $(HEADER) Makefile | $(OBJECT_PATH)
					$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJECT_PATH):
					mkdir -p $@

clean:
					$(REMOVE) $(OBJECT_PATH)

fclean:				clean
					$(REMOVE) $(NAME) $(SO)

re:					fclean all

so:
					$(CC) $(CFLAGS) -nostartfiles -fPIC  $(SOURCE_FILES)
					gcc -nostartfiles -shared -o $(SO) $(OBJECT_FILES)

.PHONY:				all clean fclean re so
