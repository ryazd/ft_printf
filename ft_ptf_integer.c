/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptf_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:31:12 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/16 17:31:14 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

char			*itoa_format(long long num, t_list **list, char *integer)
{
	int			i;

	if (num == LONG_MIN)
		integer = ft_strdup("9223372036854775808");
	else if (CSPEC->precision == 0 && num == 0)
		integer = ft_strdup("");
	else
		integer = ft_lltoa(num < 0 ? -num : num);
	i = CSPEC->precision - (int)ft_strlen(integer);
	while (i-- > 0)
		free_join(&integer, "0", 0);
	i = CSPEC->width - (int)ft_strlen(integer) - (num >= 0 && !(bit_get(1, &
	(CSPEC->flags))) && !(bit_get(3, &(CSPEC->flags))) ? 0 : 1);
	while (i-- > 0 && bit_get(2, &(CSPEC->flags)))
		free_join(&integer, "0", 0);
	if (num < 0)
		free_join(&integer, "-", 0);
	else if (bit_get(1, &(CSPEC->flags)))
		free_join(&integer, "+", 0);
	else if (bit_get(3, &(CSPEC->flags)))
		free_join(&integer, " ", 0);
	i = CSPEC->width - (int)ft_strlen(integer);
	while (i-- > 0)
		free_join(&integer, " ", bit_get(0, &(CSPEC->flags)) ? 1 : 0);
	return (integer);
}

int				print_signed_integer(char **str, t_list **list, va_list args)
{
	char		*integer;
	int			printed;

	integer = NULL;
	if (CSPEC->size == 'i')
		integer = itoa_format((signed char)va_arg(args, int), list, integer);
	else if (CSPEC->size == 'h')
		integer = itoa_format((signed short)va_arg(args, int), list, integer);
	else if (CSPEC->size == 'l')
		integer = itoa_format(va_arg(args, signed long), list, integer);
	else if (CSPEC->size == 'm')
		integer = itoa_format(va_arg(args, signed long long), list, integer);
	else
		integer = itoa_format(va_arg(args, signed int), list, integer);
	ft_putstr(integer);
	(*str) += CSPEC->cspeclen;
	printed = (int)ft_strlen(integer);
	*list = (*list)->next;
	free(integer);
	return (printed);
}

char			*utoa_format(unsigned long long num, t_list **list)
{
	char		*ui;
	int			i;

	ui = !(CSPEC->precision) && (CSPEC->type != 'o' || !(bit_get(4, &
	(CSPEC->flags)))) ? ft_strdup("") : ft_ulltoa_base(num, CSPEC->type);
	i = CSPEC->precision - (int)ft_strlen(ui);
	while (i-- > 0)
		free_join(&ui, "0", 0);
	if (bit_get(4, &(CSPEC->flags)) && CSPEC->type == 'o' && ui[0] != '0')
		free_join(&ui, "0", 0);
	i = CSPEC->width - (int)ft_strlen(ui) - (2 * ((CSPEC->type == 'x' ||
			CSPEC->type == 'X') && num && bit_get(4, &(CSPEC->flags))));
	while (i-- > 0 && bit_get(2, &(CSPEC->flags)))
		free_join(&ui, "0", 0);
	if (bit_get(4, &(CSPEC->flags)) && num != 0)
	{
		if (CSPEC->type == 'x')
			free_join(&ui, "0x", 0);
		else if (CSPEC->type == 'X')
			free_join(&ui, "0X", 0);
	}
	i = CSPEC->width - (int)ft_strlen(ui);
	while (i-- > 0)
		free_join(&ui, " ", bit_get(0, &(CSPEC->flags)) ? 1 : 0);
	return (ui);
}

int				print_unsigned_integer(char **str, t_list **list, va_list args)
{
	char		*integer;
	int			printed;

	if (CSPEC->size == 'i')
		integer = utoa_format((unsigned char)va_arg(args, int), list);
	else if (CSPEC->size == 'h')
		integer = utoa_format((unsigned short)va_arg(args, int), list);
	else if (CSPEC->size == 'l')
		integer = utoa_format(va_arg(args, unsigned long), list);
	else if (CSPEC->size == 'm')
		integer = utoa_format(va_arg(args, unsigned long long), list);
	else
		integer = utoa_format(va_arg(args, unsigned int), list);
	ft_putstr(integer);
	(*str) += CSPEC->cspeclen;
	printed = (int)ft_strlen(integer);
	*list = (*list)->next;
	free(integer);
	return (printed);
}

int				print_pointer(char **str, t_list **list, va_list args)
{
	char		*p;
	int			i;

	p = CSPEC->precision ? ft_ulltoa_base((unsigned long long)va_arg(args,
	void *), 'x') : ft_strdup("");
	i = CSPEC->precision - ft_strlen(p);
	while (i-- > 0)
		free_join(&p, "0", 0);
	free_join(&p, "0x", 0);
	i = CSPEC->width - ft_strlen(p);
	while (i-- > 0)
		free_join(&p, " ", bit_get(0, &CSPEC->flags) ? 1 : 0);
	ft_putstr(p);
	i = ft_strlen(p);
	(*str) += CSPEC->cspeclen;
	*list = (*list)->next;
	free(p);
	return (i);
}
