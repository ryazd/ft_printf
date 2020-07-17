/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:42:22 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/16 19:51:18 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include "./libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

# define SIZE sizeof(t_cspec)
# define CSPEC ((t_cspec *)(*list)->content)
# define USHORT unsigned short

typedef struct	s_cspec
{
	USHORT		flags;
	int			width;
	int			width_ast;
	int			precision;
	int			precision_ast;
	char		size;
	char		type;
	int			cspeclen;
}				t_cspec;

int				ft_printf(const char *str, ...);
void			free_join(char **integer, char *symbol, int end);
void			free_list(t_list **list);

char			*ftoa_format(long double num, t_list **list);
int				print_float(char **str, t_list **list, va_list args);
char			*btoa(long long n, int bits, t_list **list);
char			*btoa_format(long long num, t_list **list, int bits);
int				print_binary(char **str, t_list **list, va_list args);

char			*itoa_format(long long num, t_list **list, char *integer);
int				print_signed_integer(char **str, t_list **list, va_list args);
char			*utoa_format(unsigned long long num, t_list **list);
int				print_unsigned_integer(char **str, t_list **list, va_list args);
int				print_pointer(char **str, t_list **list, va_list args);

void			parse_flags(char **str, t_cspec **cspec);
void			parse_width(char **str, t_cspec **cspec);
void			parse_precision(char **str, t_cspec **cspec);
void			parse_size(char **str, t_cspec **cspec);
void			parse_type(char **str, t_cspec **cspec);

void			finalize_width(va_list args, t_list **list);
void			finalize_precision(va_list args, t_list **list);
int				print_cspec(char **str, va_list args, t_list **list, int print);
int				print_all_cspecs(char **str, va_list args, t_list **list);

t_cspec			*cspec_new(char **str);
t_list			*parse_string(char *str);
int				print_percent(char **str, t_list **list);
int				print_char(char **str, t_list **list, va_list args);
int				print_string(char **str, t_list **list, va_list args);

int				ft_strlen_non(char *s);
char			*non_print_mas(void);
int				ft_stradd_non(char **str, int pos2, int i);
char			*str_non_print(va_list args);
int				print_non_printable(char **str, t_list **list, va_list args);

#endif
