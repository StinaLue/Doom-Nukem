/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:03:56 by afonck            #+#    #+#             */
/*   Updated: 2019/07/08 16:15:21 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <wchar.h>
# include "ft_printf/includes/ft_printf.h"
# define BUFF_SIZE 8

int                             ft_printf(const char *fmt, ...);

int                             ft_dprintf(int fd, const char *fmt, ...);

int					get_next_line(const int fd, char **line);

/*
**	EXTRAS |||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

intmax_t			ft_absolute(intmax_t i);
/*
** converts a negative int into a positive int
*/

double				ft_absfloat(double number);
/*
** converts a negative double number to its positive counterpart
** (its absolute value --> if number is positive, it stays positive)
*/

double				ft_pow(double x, int y);
/*
** returns x to the power of y
*/

int					ft_nbits(unsigned int nbr);
/*
** returns the number of bits in the unsigned int nbr
*/

int					ft_wcharlen(int nbbits);
/*
** returns the length the wchar depending on its nbbits number of bits
** (use with ft_nbits)
*/

int					ft_nbrlen(intmax_t n);
/*
** returns the length of the int n
*/

int					ft_unbrlen(uintmax_t n);
/*
** returns the length of the unsigned int n
*/

int					ft_uintlen_base(uintmax_t value, int base);
/*
** returns the length of the unsigned value value from the base base
*/

int					ft_uintptrtoalen_base(uintptr_t value, int base);
/*
** returns the length of the pointer sized value from the base base
*/

int					ft_floatlen(double n, int afterpoint);
/*
** returns the length of the double n depending on the afterpoint decimal number
*/

/*
** LIST FUNCTIONS |||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
/*
** allocates a fresh chain, the *content and content_size are initialized by
** copying the params of the function. If content is NULL, content_size = 0,
** *next is initialized to NULL | returns NULL if allocation failed, or the
** fresh chainlist if it worked
*/

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
/*
** takes the address of a pointer on a chain as first param and frees the
** memory of the content of this chain with the del function (second param),
** then frees the chain in itself. The next content must NOT be freed.
** And finally, the pointer that was pointing on the chain must be set to NULL
** | doesn't return anything
*/

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
/*
** deletes and frees the whole linked list, to finish, the pointer on the first
** list is freed and then set to NULL | doesn't return anything
*/

void				ft_lstadd(t_list **alst, t_list *new);
/*
** adds the new element at the head of the linked list | doesn't return
** anything
*/

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
/*
** applies the (*f) function on each element of the lst list | doesn't return
** anything
*/

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
/*
** applies to each element of the linked list the function (*f) and creates
** a new fresh list out of the result of this application | returns NULL if
** an allocation failed / the new fresh list otherwise
*/

/*
** PUT (PRINT) FUNCTIONS ||||||||||||||||||||||||||||||||||||||||||||||||||
*/

void				ft_putchar(char c);
/*
** prints the char c with write on the standard input |
** doesn't return anything
*/
int					ft_putwchar_fd(wchar_t wchar, int fd);
/*
** prints the wide char wchar in the file descriptor fd, returns the length
** of the wchar
*/

void				ft_putstr(char const *s);
/*
** prints the s string on the standard input | doesn't
** return anything
*/

int					ft_putwstr_fd(wchar_t *str, int fd);
/*
** prints the wide char string str on the file descriptor fd, returns the
** length of the wide string
*/

void				ft_putendl(char const *s);
/*
** prints the s string + a newline | doesn't return
** anything
*/

void				ft_putchar_fd(char c, int fd);
/*
** writes the char c in the file descriptor fd | doesn't return anything
*/

void				ft_putstr_fd(char const *s, int fd);
/*
** writes the string s in the file descriptor fd | doesn't return anything
*/

void				ft_putendl_fd(char const *s, int fd);
/*
** prints the s string in the file descriptor fd, with a new line at the
** end | doesn't return anything
*/

void				ft_putnbr(int n);
/*
** prints the int n on the standard input | doesn't return anything
*/

void				ft_putnbr_fd(intmax_t n, int fd);
/*
** prints the int n on the file descriptor fd | doesn't return anything
*/

int					ft_ftoa_fd(double n, int afterpoint, int fd);
/*
** prints the double n with afterpoint decimal numbers in the file descriptor fd
*/

int					ft_uitoa_base(uintmax_t value, int base, int fd);
/*
** prints the unsigned value in the base base, in small letters from a, on
** the file descriptor fd
*/

int					ft_uitocapa_base(uintmax_t value, int base, int fd);
/*
** prints the unsigned value int the base base, in capital letters from A, on
** the file descriptor fd
*/

int					ft_uintptrtoa_base(uintptr_t value, int base, int fd);
/*
** prints the pointer sized value in base base in file descriptor fd
*/

/*
** STR FUNCTIONS |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

size_t				ft_strlen(const char *s);
/*
** counts nb of characters in s string | returns the nb
*/

int					ft_wstrlen(wchar_t *wstr);
/*
** returns the size of the wide string wstr
*/

char				*ft_strdup(const char *s1);
/*
** duplicates s1 string | returns the new duplicated string
*/

int					ft_strcmp(const char *s1, const char *s2);
/*
** compares the s1 string with the s2 string | returns
** int > 0 (if s1 > s2) / int = 0 (if s1 = s2) / int < 0 (if s1 < s2)
*/

int					ft_strncmp(const char *s1, const char *s2, size_t n);
/*
** same function as ft_strcmp, but doesn't compare more than n characters
*/

char				*ft_strcpy(char *dst, const char *src);
/*
** copies the string src to dst (including terminating '\0') | returns dst
*/

char				*ft_strncpy(char *dst, const char *src, size_t len);
/*
** same function as ft_strcpy, but doesn't copy more than len characters
*/

char				*ft_strcat(char *s1, const char *s2);
/*
** appends s2 copy at the end of s1 (including end '\0') | returns s1
*/

char				*ft_strncat(char *s1, const char *s2, size_t n);
/*
** same function as ft_strcat, but doesn't append more than n characters
*/

size_t				ft_strlcat(char *dst, const char *src, size_t size);
/*
** safer version of strcat, returns full length of the string that was
** tried to create. NOTE: size should be the size of the full string after
** concatenation / if size < len(dst) + 1 ('\0'), return size + len(src)
*/

char				*ft_strchr(const char *s, int c);
/*
** locates the first occurence of c (converted to char) in the string
** pointed to by s (works also with '\0' as c) | returns a pointed to the
** located character OR NULL if char doesn't appear
*/

char				*ft_strrchr(const char *s, int c);
/*
** same function as ft_strchr, but only returns a pointer to the last
** occurence of char c
*/

char				*ft_strstr(const char *haystack, const char *needle);
/*
** locates first occurence of the needle string in the haystack
** string | returns haystack if needle is empty / NULL if needle
** occurs nowhere in haystack / or a pointer to the first char
** of needle first occurence if found
*/

char				*ft_strnstr(const char *haystack, const char *needle,\
					size_t len);
/*
** same function as ft_strstr, but only until len characters in haystack
*/

char				*ft_strnew(size_t size);
/*
** allocates a fresh new string with malloc where each char is
** initialized to '\0', including the terminating char | returns the
** fresh string, or NULL if the allocation failed
*/

void				ft_strdel(char **as);
/*
** takes the address of a string as a parameter, frees this string
** and sets it to NULL | doesn't return anything
*/

void				ft_strclr(char *s);
/*
** sets each character of the s string as '\0' | doesn't return
** anything
*/

void				ft_striter(char *s, void (*f)(char *));
/*
** applies f function to each character (passed as an address) of the
** s string, modifies the char if necessary | doesn't return anything
*/

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
/*
** same function as ft_striter, but adds the index of the pointed
** char as the first argument of the function pointer (*f) |
** doesn't return anything
*/

char				*ft_strmap(char const *s, char (*f)(char));
/*
** applies the (*f) function to each char of the s string |
** returns a fresh string that is the result of the s string in
** which each char was passed to the (*f) function
*/

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*
** same function as ft_strmap, but also precises the index in the
** function parameters
*/

int					ft_strequ(char const *s1, char const *s2);
/*
** compares lexicographically s1 with s2 | returns 1 if s1 == s2,
** 0 if not
*/

int					ft_strnequ(char const *s1, char const *s2, size_t n);
/*
** same function as ft_strequ, but doesn't compare more than n char,
** or until a '\0' was found | returns 1 if s1 == s2, 0 if not
*/

char				*ft_strsub(char const *s, unsigned int start, size_t len);
/*
** allocates a fresh copy of a substring (going from start, with a
** len length) of the full string s | returns the substring, or
** NULL if malloc failed
*/

char				*ft_strjoin(char const *s1, char const *s2);
/*
** allocates a fresh new string resulting from the concatenation
** of s1 with s2 | returns the new string, or NULL if malloc failed
*/

char				*ft_strtrim(char const *s);
/*
** allocates a fresh new copy of s, trimming out all the
** whitespaces (' ' / '\n' / '\t') | returns s if there is nothing
** to trim, or a fresh new trimmed string if there is
*/

char				**ft_strsplit(char const *s, char c);
/*
** allocates a fresh new tab in which each case is a word delimited
** by the separator c | returns the tab, or NULL if it failed
*/

/*
** BOOLEANS ||||||||||||||||||||||||||||||||||||||||||||||||||
*/

int					ft_isalpha(int c);
/*
** check if int (type casted as char) c is an alphabetical letter (BIG
** or small) of the ASCII table | returns 1 if yes, 0 if not
*/

int					ft_isdigit(int c);
/*
** same function as ft_isalpha, but for character digits on the ASCII
** table | returns 1 if yes, 0 if not
*/

int					ft_isalnum(int c);
/*
** same function as above, but checks true for alpha OR number |
** returns 1 if c is alpha or num, 0 if not
*/

int					ft_isascii(int c);
/*
** checks if c (type casted as char) is an ascii character (special chars
** included) | returns 1 if yes, 0 if not
*/

int					ft_isprint(int c);
/*
** checks if character c is a printable char of the ASCII table | returns
** 1 if yes, 0 if not
*/

/*
** CONVERSION ||||||||||||||||||||||||||||||||||||||||||||||
*/

int					ft_atoi(const char *str);
/*
** converts possible portion of the string str to an int | returns the
** converted int
*/

long long			ft_atol(const char *str);
/*
** converts possible portion of the string str to a long long | returns the
** converted long long
*/

char				*ft_itoa(int n);
/*
** allocates a fresh new string representating the int passed as a
** parameter (char by char) | returns the new string
*/

int					ft_toupper(int c);
/*
** if char c is a small letter, transforms it into a big one | returns
** the new big letter, or the unchanged c if c is not a small letter
*/

int					ft_tolower(int c);
/*
** if char c is a big letter, transforms it into a small one | returns
** the new small letter, or the unchanged c if c is not a big letter
*/

/*
** MEMORY |||||||||||||||||||||||||||||||||||||||||||||||||||
*/

void				*ft_memset(void *b, int c, size_t len);
/*
** writes len bytes of value c (converted to unsigned char) to string b |
** returns a pointed to the first char of string b
*/

void				ft_bzero(void *s, size_t n);
/*
** same function as ft_memset but fills the string with null bytes
** instead | doesn't return anything
*/

void				*ft_memcpy(void *dst, const void *src, size_t n);
/*
** copies n bytes from memory area src to memory area dst | returns original
** pointer dst
*/

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
/*
** copies bytes from src to dst. If char c (converted to unsigned char)
** occurs in src, copy stops; else, n bytes are copied | returns pointer
** to byte after the copy of c in dst / else, n bytes copied, NULL pointer
** returned
*/

void				*ft_memmove(void *dst, const void *src, size_t len);
/*
** same function as ft_memcpy, but handles overlapping so that no data of dst
** is lost | returns the original pointer dst
*/

void				*ft_memchr(const void *s, int c, size_t n);
/*
** locates first occurence of c (type casted as an unsigned char) if it exists
** within n bytes | returns a pointer to that byte if it exists, NULL if not
*/

int					ft_memcmp(const void *s1, const void *s2, size_t n);
/*
** compares the byte string s1 with the byte string s2, both strings are
** assumed to be n bytes long | returns 0 if s1 and s2 are identical,
** otherwise returns the difference between the first two different
** bytes
*/

void				*ft_memalloc(size_t size);
/*
** allows a fresh block of memory of size (size) | returns a pointer to
** that memory
*/

void				ft_memdel(void **ap);
/*
** frees the ap pointer and sets it to NULL | doesn't return anything
*/

#endif
