/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:38:26 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 13:43:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdint.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_pair_d
{
	double			a;
	double			b;
}					t_pair_d;

/*
** libc functions
*/
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncat(char *dest, char *src, size_t nb);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,\
								size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** additional functions
*/
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** bonus functions
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstappend(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstat(t_list *lst, unsigned int n);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnewptr(const void *ptr);

/*
** extra functions
*/
char				*ft_strrev(char *str);
int					ft_nwords(char *str, char delim);
long long			ft_pow(long long n, unsigned int p);
int					ft_min(int a, int b);
int					ft_max(int a, int b);
char				*ft_dtoa(long double d, int precision);
char				*ft_itoa_base(int n, char *digits);
int					ft_ndigits(int n);
int					ft_ndigits_base(int n, int base);
int					ft_ndigits_base_ll(long long n, int base);
int					ft_ndigits_base_ull(unsigned long long n, int base);
char				*ft_itoa_ll(long long n);
char				*ft_itoa_ull(unsigned long long n);
char				*ft_itoa_base_ull(unsigned long long n, char *digits);
int					ft_abs(int i);
t_pair_d			ft_make_pair_d(double a, double b);
double				ft_map_range(double v, t_pair_d a, t_pair_d b);
double				ft_abs_d(double d);
char				*ft_strtok(char *src, const char *delims);
int					ft_ndigits_d(long double d);
double				ft_strtod(char *str);
void				ft_free_array(void **arr);

void				ft_swap_f(float *f1, float *f2);
void				ft_swap_d(double *d1, double *d2);
double				ft_max_d(double a, double b);
float				ft_lerp_f(float n1, float n2, float t);
float				ft_inv_lerp_f(float value, float a, float b);
double				ft_lerp_d(double n1, double n2, double t);
double				ft_inv_lerp_d(double value, double a, double b);
double				ft_clamp_d(double d, double min, double max);
double				ft_clamp_d0(double d, double min, double max);
double				ft_deg_to_rad(double deg);
double				ft_rad_to_deg(double rad);
double				ft_rand_d(int *seed);
double				ft_clamp_range(double v, double min, double max);
double				ft_pow_d(double n, unsigned int p);

#endif
