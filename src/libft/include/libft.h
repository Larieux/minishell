/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:08:40 by mlarieux          #+#    #+#             */
/*   Updated: 2025/01/15 17:35:46 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9
# endif

# ifndef MAX_FD
#  define MAX_FD 128
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief concatenate strings
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @return size_t 
 */
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/**
 * @brief It  returns an integer less than, equal to, or greater than
 * zero if s1 is found, respectively, to be less than,  to  match,  or  be
 * greater than s2.
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strnrcmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *nptr);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/**
 * @brief returns a pointer to the first occurrence of the
 * character c in the string s.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char		*ft_strchr(const char *s, int c);

/**
 * @brief returns a pointer to the last occurrence of  the
 * character c in the string s.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char		*ft_strrchr(const char *s, int c);

/**
 * @brief The strnstr() function locates the first occurrence of the null-termi‐
 * nated string little in the string big, where not more than len characters
 * are searched.
 * 
 * @param big 
 * @param little 
 * @param len 
 * @return char* 
 */
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);

/**
 * @brief Allocates (with malloc(3)) and returns a substring
 * from the string ’s’.
 * The substring begins at index ’start’ and is of
 * maximum size ’len’.
 * 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief 
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char		*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 * 
 * @param s1 
 * @param set 
 * @return char* 
 */
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting ’s’ using the
 * character ’c’ as a delimiter. The array must end
 * with a NULL pointer.
 * 
 * @param s 
 * @param c 
 * @return char** 
 */
char		**ft_split(char const *s, char c);

/**
 * @brief frees a double array
 * 
 * @param tab 
 */
void		free_dtab(char **dtab);

/* ************************************************************************** */
/* 																			  */
/* 									linked-lists							  */
/* 																			  */
/* ************************************************************************** */

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list **lst, t_list *node);
void		ft_lstclear(t_list **lst);
int			ft_lstsize(t_list *lst);

/* ************************************************************************** */
/* 																			  */
/* 									get_next_line							  */
/* 																			  */
/* ************************************************************************** */

size_t		ft_strlcat_gnl(char *dst, const char *src, size_t size);
size_t		ft_strlen_gnl(const char *s);
size_t		ft_strlcpy_gnl(char *dst, const char *src, size_t size);
char		*ft_strjoin_gnl(char *s1, char *s2);
bool		test_old_line_gnl(char *buffer);
bool		test_new_line_gnl(char *line);
char		*make_line_gnl(char *line, char *buffer, int fd, ssize_t size);

/**
 * @brief Get the next line object
 * 
 * @param fd 
 * @return char* 
 */
char		*get_next_line(int fd);

#endif