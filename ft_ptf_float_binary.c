/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptf_float_binary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:32:54 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/16 17:32:55 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

char			*ftoa_format(long double num, t_list **list)
{
	char		*f;
	int			i;

	f = ft_ldtoa(num, CSPEC->precision);
	i = CSPEC->width - (int)ft_strlen(f) - (num >= 0 && !(bit_get(1, &
			(CSPEC->flags))) && !(bit_get(3, &(CSPEC->flags))) ? 0 : 1);
	while (i-- > 0 && bit_get(2, &(CSPEC->flags)))
		free_join(&f, "0", 0);
	if (num < 0)
		free_join(&f, "-", 0);
	else if (bit_get(1, &(CSPEC->flags)))
		free_join(&f, "+", 0);
	else if (bit_get(3, &(CSPEC->flags)))
		free_join(&f, " ", 0);
	if (bit_get(4, &(CSPEC->flags)) && !ft_strchr(f, '.'))
		free_join(&f, ".", 1);
	i = CSPEC->width - (int)ft_strlen(f);
	while (i-- > 0)
		free_join(&f, " ", bit_get(0, &(CSPEC->flags)) ? 1 : 0);
	return (f);
}

int				print_float(char **str, t_list **list, va_list args)
{
	char		*f;
	int			printed;

	if (CSPEC->size == 'L')
		f = ftoa_format(va_arg(args, long double), list);
	else
		f = ftoa_format(va_arg(args, double), list);
	ft_putstr(f);
	(*str) += CSPEC->cspeclen;
	printed = (int)ft_strlen(f);
	*list = (*list)->next;
	free(f);
	return (printed);
}

char			*btoa(long long n, int bits, t_list **list)
{
	char		*result;
	int			neg;

	neg = n < 0 ? 1 : 0;
	result = ft_strdup("");
	if (n < 0)
		n = -n;
	while (bits-- > 0 && n > 0)
	{
		free_join(&result, n % 2 ? "1" : "0", 0);
		n /= 2;
		if (!(bits % 4) && bit_get(3, &(CSPEC->flags)))
			free_join(&result, " ", 0);
	}
	while (bits-- > 0)
		free_join(&result, !((bits + 1) % 4) && bit_get(3, &(CSPEC->flags)) ?
		" 0" : "0", 0);
	free_join(&result, neg ? "1" : "0", 0);
	return (result);
}

char			*btoa_format(long long num, t_list **list, int bits)
{
	char		*b;

	if (bits == 8 && num == -128)
		return (ft_strdup("1000 0000"));
	else if (bits == 16 && num == -32768)
		return (ft_strdup("1000 0000 0000 0000"));
	else if (bits == 32 && num == -2147483648)
		return (ft_strdup("1000 0000 0000 0000 0000 0000 0000 0000"));
	else if (bits == 64 && num == LONG_LONG_MIN)
		b = ft_strjoin("1000 0000 0000 0000 0000 0000 0000 0000 0000 0000 ",
				"0000 0000 0000 0000 0000 0000");
	else
		b = btoa(num, bits, list);
	return (b);
}

int				print_binary(char **str, t_list **list, va_list args)
{
	char		*b;
	int			printed;

	if (CSPEC->size == 'i')
		b = btoa_format((signed char)va_arg(args, int), list, 8);
	else if (CSPEC->size == 'h')
		b = btoa_format((signed short)va_arg(args, int), list, 16);
	else if (CSPEC->size == 'l')
		b = btoa_format(va_arg(args, signed long), list, 32);
	else if (CSPEC->size == 'm')
		b = btoa_format(va_arg(args, signed long long), list, 64);
	else
		b = btoa_format(va_arg(args, signed int), list, 32);
	ft_putstr(b);
	(*str) += CSPEC->cspeclen;
	printed = (int)ft_strlen(b);
	*list = (*list)->next;
	free(b);
	return (printed);
}
