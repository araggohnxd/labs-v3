/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:43:19 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/29 15:33:43 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// External libraries
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

// Macros and enumerators
# ifndef STDIN
#  define STDIN STDIN_FILENO
# endif
# ifndef STDOUT
#  define STDOUT STDOUT_FILENO
# endif
# ifndef STDERR
#  define STDERR STDERR_FILENO
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define MAX_FD_VALUE 1024
# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"
# define CHAR 'c'
# define STR 's'
# define PTR 'p'
# define DEC 'd'
# define INT 'i'
# define UINT 'u'
# define HEXL 'x'
# define HEXU 'X'
# define PERCENT '%'

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

// Type definitions
typedef long long			t_llong;
typedef unsigned int		t_uint;
typedef unsigned long		t_ulong;
typedef unsigned long long	t_ullong;

/* The basic structure of a linked list node. */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*


PART 1 - LIBC FUNCTIONS


*/
/**
* @brief Verifies if c is an alphabetic character.
* @param c Character to be verified.
* @return 1 if character is alphabetic, else returns 0.
*/
int		ft_isalpha(int c);

/**
* @brief Verifies if c is a numeric character.
* @param c Character to be verified.
* @return 1 if character is numeric, else returns 0.
*/
int		ft_isdigit(int c);

/**
* @brief Verifies if c is an alphanumeric character.
* @param c Character to be verified.
* @return 1 if character is alphanumeric, else returns 0.
*/
int		ft_isalnum(int c);

/**
* @brief Verifies if c is an ASCII character.
* @param c Character to be verified.
* @return 1 if character is in ASCII, else returns 0.
*/
int		ft_isascii(int c);

/**
* @brief Verifies if c is a printable character.
* @param c Character to be verified.
* @return 1 if character is printable, else returns 0.
*/
int		ft_isprint(int c);

/**
* @brief Transform a lowercase character into an uppercase character.
* @param c Character to be transformed.
* @return The transformed character, or itself if it is already
* uppercase.
*/
int		ft_toupper(int c);

/**
* @brief Transform an uppercase character into a lowercase character.
* @param c Character to be transformed.
* @return The transformed character, or itself if it is already
* lowercase.
*/
int		ft_tolower(int c);

/**
* @brief Compares at most n bytes of two strings
* (each interpreted as unsigned char)
* by its ASCII values.
* @param s1 First string.
* @param s2 Second string.
* @param n Number of bytes to compare.
* @return -1, 0 or 1 if s1 is less, equal or greater than s2,
* respectively.
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
* @brief Compare at most n bytes of two memory areas
* (each interpreted as unsigned char)
* by its ASCII values.
* @param s1 First area.
* @param s2 Second area.
* @param n Number of bytes to compare.
* @return -1, 0 or 1 if s1 is less, equal or greater than s2,
* respectively.
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
* @brief Converts the initial portion of the string pointed to by nptr to int.
* @param nptr The string to be converted.
* @return Converted value or 0 on error.
*/
int		ft_atoi(const char *nptr);

/**
* @brief Erases the data in the n bytes of the memory starting at the
* location pointed to by s, by writing zeros
* (bytes containing '\0') to that area.
* @param s Memory area to erase.
* @param n Number of bytes to erase.
* @return Nothing.
*/
void	ft_bzero(void *s, size_t n);

/**
* @brief Returns a pointer to a new string which is a duplicate of the string s.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s String to duplicate.
* @return A pointer to the new string or NULL on error.
*/
char	*ft_strdup(const char *s);

/**
* @brief Locates the first occurrence of the null-terminated string needle
* in the string haystack, where not more than len characters are searched.
* @param haystack String to be searched.
* @param needle Substring to search in haystack.
* @param len Number of bytes to search (at most, needle length).
* @return A pointer to the first occurence of needle string or NULL on error.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
* @brief Returns a pointer to the first occurrence
* of the character c in the string s
* (interpreted as unsigned char).
* @param s String to be searched.
* @param c Character to search for.
* @return A pointer to the first occurrence of c in s or NULL if not found.
*/
char	*ft_strchr(const char *s, int c);

/**
* @brief Returns a pointer to the last occurrence
* of the character c in the string s
* (interpreted as unsigned char).
* @param s String to be searched.
* @param c Character to search for.
* @return A pointer to the last occurrence of c in s or NULL if not found.
*/
char	*ft_strrchr(const char *s, int c);

/**
* @brief Fills the first n bytes of the memory area
* pointed to by s with the constant byte c.
* @param s Memory area to fill.
* @param c Byte to fill with.
* @param n Number of bytes to fill.
* @return A pointer to the memory area s.
*/
void	*ft_memset(void *s, int c, size_t n);

/**
* @brief Copies n bytes from memory area src to memory area dest.
* The memory areas must not overlap.
* @param dest Destination memory area.
* @param src Source memory area.
* @param n Number of bytes to copy.
* @return A pointer to the memory area dest.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
* @brief Copies n bytes from memory area src to memory area dest.
* The memory areas can overlap.
* @param dest Destination memory area.
* @param src Source memory area.
* @param n Number of bytes to copy.
* @return A pointer to the memory area dest.
*/
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
* @brief Scans the initial n bytes of the memory area
* pointed to by s for the first instance of c
* (both interpreted as unsigned char).
* @param s Memory area to scan.
* @param c Character to scan for.
* @param n Number of bytes to scan.
* @return
*/
void	*ft_memchr(const void *s, int c, size_t n);

/**
* @brief Allocates memory for an array of nmemb elements of size bytes each
* and returns a pointer to the allocated memory. The memory is set to zero.
* If nmemb or size is 0, then ft_calloc() returns either NULL,
* or a unique pointer value that can later be successfully passed to
* free(). If the multiplication of nmemb and size would result in integer
* overflow, then ft_calloc() returns an error.
* @param nmemb Number of elements that need allocation.
* @param size Size of bytes required by each element.
* @return A pointer to the allocated memory or NULL on error.
*/
void	*ft_calloc(size_t nmemb, size_t size);

/**
* @brief Calculates the length of the string pointed to by s,
* excluding the terminating null byte ('\0').
* @param s String to calculate length of.
* @return The number of bytes in the string pointed to by s.
*/
size_t	ft_strlen(const char *s);

/**
* @brief Copies up to size - 1 characters from the NUL-terminated
*  string src to dst, NUL-terminating the result.
* @param dst Destination string.
* @param src Source string.
* @param size Size in bytes of the full buffer
* (src length + 1 for the null byte).
* @return The total length of the string it tried to create
* (src length).
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
* @brief Function appends the NUL-terminated string src to the end of dst.
* It will append at most size - strlen(dst) - 1 bytes,
* NUL-terminating the result.
* @param dst Destination string.
* @param src Source string.
* @param size Size in bytes of the full buffer
* (dst length + src length + 1 for the null byte).
* @return The total length of the string it tried to create
* (src length + dst length).
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/*


PART 2 - ADDITIONAL FUNCTIONS


*/
/**
* @brief Converts the integer n
* to a string representation of the given number.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param n Integer to convert.
* @return A pointer to the created string containing the number.
*/
char	*ft_itoa(int n);

/**
* @brief Creates a new string, which is the result
* of the concatenation of s1 and s2.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s1 First string.
* @param s2 Second string.
* @return A pointer to the created string or NULL on error.
*/
char	*ft_strjoin(char const *s1, char const *s2);

/**
* @brief Creates a new string, which is the result
* of the concatenation of s1 and s2, then free()s both s1 and s2.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s1 First string.
* @param s2 Second string.
* @return A pointer to the created string or NULL on error.
*/
char	*ft_strjoin_free(char **s1, char **s2);

/**
* @brief Creates a copy of s1 with the characters specified in set
* removed from the beginning and the end of the string.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s1 String to trim from.
* @param set Set of characters to trim.
* @return A pointer to the trimmed string or NULL on error.
*/
char	*ft_strtrim(char const *s1, char const *set);

/**
* @brief Creates a substring from the string s.
* The substring begins at index start and is of maximum size len.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s String to be searched.
* @param start Offset byte of the substring inside the string s.
* @param len Size of the substring.
* @return A pointer to the created substring or NULL on error.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
* @brief Applies the function f to each character of the string s,
* and passes its index as first argument to create a new string
* resulting from successive applications of f.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s String to be iterated.
* @param f Function to apply to each character of the string s.
* @param f(uint) Current index of the string s.
* @param f(char) Character found in the current index of string s.
* @return A pointer to the string created from the successive applications
* of f or NULL on error.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
* @brief Creates an array of strings obtained by splitting s using the
* character c as a delimiter. The array must end with a NULL pointer.
* Memory for the array of strings and the strings inside it
* is obtained with malloc(), and can be freed with free().
* @param s String to be splitted.
* @param c Character used as delimiter.
* @return A pointer to the created array of strings or NULL on error.
*/
char	**ft_split(char const *s, char c);

/**
* @brief Applies the function f on each character of the string
* passed as argument, passing its index as first argument.
* Each character is passed by address to f to be modified if necessary.
* @param s String to be iterated.
* @param f Function to apply to each character of the string s.
* @param f(uint) Current index of the string s.
* @param f(char*) Address of the character found in the current
* index of string s.
* @return Nothing.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
* @brief Outputs the character c to the given file descriptor.
* @param c Character to output.
* @param fd File descriptor to write to.
* @return Nothing.
*/
void	ft_putchar_fd(char c, int fd);

/**
* @brief Outputs the string s to the given file descriptor.
* @param s String to output.
* @param fd File descriptor to write to.
* @return Nothing.
*/
void	ft_putstr_fd(char *s, int fd);

/**
* @brief Outputs the string s to the given file descriptor,
* followed by a newline.
* @param s String to output.
* @param fd File descriptor to write to.
* @return Nothing.
*/
void	ft_putendl_fd(char *s, int fd);

/**
* @brief Outputs the integer n to the given file descriptor.
* @param n Number to output.
* @param fd File descriptor to write to.
* @return Nothing.
*/
void	ft_putnbr_fd(int n, int fd);

/*


BONUS PART


*/
/**
* @brief Counts the number of nodes in a list.
* @param lst Beggining of the list (head node).
* @return The length of the list.
*/
int		ft_lstsize(t_list *lst);

/**
* @brief Adds the node new at the beginning of the list lst.
* @param lst The address of a pointer to the first node of a list.
* @param new Node to be added to the list.
* @return Nothing.
*/
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
* @brief Adds the node new at the end of the list lst.
* @param lst The address of a pointer to the first node of a list.
* @param new Node to be added to the list.
* @return Nothing.
*/
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
* @brief Takes as a parameter a node and frees the memory of the
* node’s content using the function del given as a parameter and
* free the node. The memory of next must not be freed.
* @param lst Node to delete the content from and free.
* @param del Function used to delete the node's content.
* @param del(void*) Content to be deleted by del.
* @return Nothing.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
* @brief Deletes and frees the given node and every successor of
* that node, using the function del and free(). Finally, the
* pointer to the list must be set to NULL.
* @param lst The address of a pointer to a node.
* @param del Function used to delete the content of the node.
* @param del(void*) Content to be deleted by del.
* @return Nothing.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
* @brief Iterates the list lst and applies the function f
* on the content of each node.
* @param lst Pointer to a node.
* @param f Function to apply to each node of lst.
* @param f(void*) Content of the node.
* @return Nothing.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
* @brief Creates a new node. The member variable content is initialized
* with the value of the parameter content.
* The variable next is initialized to NULL.
* Memory for the new node and its members is obtained with malloc(),
* and can be freed with free().
* @param content Content to initialize the node with.
* @return A pointer to the created node or NULL on error.
*/
t_list	*ft_lstnew(void *content);

/**
* @brief Finds the last node in a list.
* @param lst List to be searched
* @return A pointer to the last node in the list or NULL on error.
*/
t_list	*ft_lstlast(t_list *lst);

/**
* @brief Iterates the list lst and applies the function f on the
* content of each node. Creates a new list resulting of the
* successive applications of the function f. The del function
* is used to delete the content of a node if needed.
* @param lst Pointer to a node.
* @param f Function to apply to each node of lst.
* @param del Function used to delete a node if needed.
* @param f(void*) Content of the node to be iterated.
* @param del(void*) Content of the node to be deleted.
* @return A pointer to the head of the new list or NULL on error.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*


ADDED LATER


*/
/**
* @brief Verifies if c is a space character.
* @param c Character to be verified.
* @return 1 if character is space, else returns 0.
*/
int		ft_isspace(int c);

/**
* @brief Calculates the length of the string pointed to by s,
* excluding the terminating null byte ('\0'), but at most maxlen.
* In doing this, ft_strnlen() looks only at the first maxlen characters
* in the string pointed to by s and never beyond s[maxlen-1].
* @param s String to calculate length of.
* @param maxlen Maximun amount of characters to calculate.
* @return The number of bytes among the first maxlen characters
* in the string pointed to by s.
*/
size_t	ft_strnlen(const char *s, size_t maxlen);

/**
* @brief Free ptr and point it to NULL.
* @param ptr Memory to be freed.
* @return Nothing.
*/
void	ft_memfree(void	**ptr);

/**
* @brief Frees the memory of a matrix of any type.
* @param matrix Matrix to be freed.
* @return Nothing.
*/
void	ft_free_matrix(void ***matrix);

/**
* @brief Converts the unsigned integer n
* to a string representation of the given number.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param n Unsigned integer to convert.
* @return A pointer to the created string containing the number.
*/
char	*ft_utoa(t_uint n);

/**
* @brief Converts the decimal base integer n
* to a string representation of the given number
* in the base received as parameter.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param n Decimal to convert.
* @param base Base to convert to.
* @return A pointer to the created string containing the number.
*/
char	*ft_itoa_base(t_ulong n, char *base);

/**
* @brief Converts the initial portion of the string pointed to by nptr to
* long long.
* @param nptr The string to be converted.
* @return Converted value or 0 on error.
*/
t_llong	ft_atoll(const char *nptr);

/**
* @brief Compares two strings
* (each interpreted as unsigned char)
* by its ASCII values.
* @param s1 First string.
* @param s2 Second string.
* @param n Number of bytes to compare.
* @return -1, 0 or 1 if s1 is less, equal or greater than s2,
* respectively.
*/
int		ft_strcmp(const char *s1, const char *s2);

/**
* @brief Skip specific characters on a string, using function f,
* received as a parameter.
* @param str String to skip characters from.
* @param f Function used to check characters that should be skipped.
* @param f(int) Char to be checked.
* @return Nothing.
*/
void	ft_skip_chars(char *str, int (*f)(int));

/**
* @brief Creates a copy of s1 with the characters specified in set
* removed from the beginning and the end of the string, then
* free()s s1.
* Memory for the new string is obtained with malloc(),
* and can be freed with free().
* @param s1 String to trim from.
* @param set Set of characters to trim.
* @return A pointer to the trimmed string or NULL on error.
*/
char	*ft_strtrim_free(char **s1, char const *set);

/*


GET_NEXT_LINE & FT_PRINTF


*/
/**
* @brief Read and return a line from a given file descriptor.
* Consecutive calls to this function will return the next line of the file
* descriptor, until EOF.
* @param fd The file descriptor to read from.
* @return A pointer to a string containing the line read,
* or NULL if EOF is reached or an error occurs.
*/
char	*ft_gnl(int fd);

/**
* @brief Read and return a line from a given file descriptor.
* Consecutive calls to this function will return the next line of the file
* descriptor, until EOF. This version can handle multiple file descriptors.
* @param fd The file descriptor to read from.
* @return A pointer to a string containing the line read,
* or NULL if EOF is reached or an error occurs.
*/
char	*ft_gnl_multifd(int fd);

/**
* @brief Print an output to the standard output stream (terminal),
* according to a format specified as a parameter
* (accepted arguments: cspdiuxX%).
* @param format Desired output formatting.
* @param ... Variadic arguments.
* @return The number of characters printed.
*/
int		ft_printf(const char *format, ...);

/**
* @brief Handles ft_printf()'s %d and %i specifiers.
* @param number Decimal or integer to be printed.
* @return The number of characters printed.
*/
int		ft_handler_integer(int number);

/**
* @brief Handles ft_printf()'s %u specifier.
* @param number Unsigned number to be printed.
* @return The number of characters printed.
*/
int		ft_handler_unsigned(t_uint number);

/**
* @brief Handles ft_printf()'s %x and %X specifiers.
* @param specifier Specifier for lowercase or uppercase.
* @param number Number to be converted to
* hexadecimal and printed.
* @return The number of characters printed.
*/
int		ft_handler_hex(char specifier, t_uint number);

/**
* @brief Handles ft_printf()'s %p specifier.
* @param pointer Pointer to have it's
* address printed.
* @return The number of characters printed.
*/
int		ft_handler_pointer(void *pointer);

/**
* @brief Handles ft_printf()'s %s specifier.
* @param string String to be printed.
* @return The number of characters printed.
*/
int		ft_handler_string(char *string);

#endif /* LIBFT_H */
