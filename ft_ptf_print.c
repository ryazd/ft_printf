/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptf_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:37:28 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/16 17:37:30 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

void			finalize_width(va_list args, t_list **list)
{
	if (CSPEC->width_ast)
	{
		if (CSPEC->width)
			va_arg(args, int);
		else
			CSPEC->width = va_arg(args, int);
	}
	if (CSPEC->width < 0)
	{
		bit_set(0, &(CSPEC->flags));
		CSPEC->width = -(CSPEC->width);
	}
}

void			finalize_precision(va_list args, t_list **list)
{
	if (CSPEC->precision_ast)
	{
		if (CSPEC->precision)
			va_arg(args, int);
		else
			CSPEC->precision = va_arg(args, int);
	}
	if (CSPEC->precision >= 0 && CSPEC->type != 'f')
		bit_reset(2, &(CSPEC->flags));
	if (CSPEC->precision < 0)
	{
		if (CSPEC->type == 'd' || CSPEC->type == 'i' || CSPEC->type == 'o'
			|| CSPEC->type == 'u' || CSPEC->type == 'x' || CSPEC->type == 'X')
			CSPEC->precision = 1;
		else if (CSPEC->type == 'f')
			CSPEC->precision = 6;
	}
}

int				print_cspec(char **str, va_list args, t_list **list, int print)
{
	print = 0;
	finalize_width(args, list);
	finalize_precision(args, list);
	if (CSPEC->type == '%')
		print = print_percent(str, list);
	else if (CSPEC->type == 'c')
		print = print_char(str, list, args);
	else if (CSPEC->type == 's')
		print = print_string(str, list, args);
	else if (CSPEC->type == 'd' || CSPEC->type == 'i')
		print = print_signed_integer(str, list, args);
	else if (CSPEC->type == 'u' || CSPEC->type == 'o' || CSPEC->type == 'x'
	|| CSPEC->type == 'X')
		print = print_unsigned_integer(str, list, args);
	else if (CSPEC->type == 'p')
		print = print_pointer(str, list, args);
	else if (CSPEC->type == 'f')
		print = print_float(str, list, args);
	else if (CSPEC->type == 'b')
		print = print_binary(str, list, args);
	else if (CSPEC->type == 'r')
		print = print_non_printable(str, list, args);
	else
		(*str) += CSPEC->cspeclen - 1;
	return (print);
}

int				print_all_cspecs(char **str, va_list args, t_list **list)
{
	int			printed;

	printed = 0;
	while (**str)
	{
		if (**str != '%')
		{
			write(1, (*str)++, 1);
			printed++;
		}
		else
			printed += print_cspec(str, args, list, printed);
	}
	return (printed);
}
