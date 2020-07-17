/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:21:11 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/16 17:21:16 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

void			parse_flags(char **str, t_cspec **cspec)
{
	(*cspec)->flags = 0;
	while (**str == '-' || **str == '+' || **str == '0' || **str == ' ' ||
	**str == '#')
	{
		(*cspec)->cspeclen += 1;
		if (**str == '-')
			bit_set(0, &((*cspec)->flags));
		else if (**str == '+')
			bit_set(1, &((*cspec)->flags));
		else if (**str == '0')
			bit_set(2, &((*cspec)->flags));
		else if (**str == ' ')
			bit_set(3, &((*cspec)->flags));
		else if (**str == '#')
			bit_set(4, &((*cspec)->flags));
		(*str)++;
	}
	if (bit_get(0, &((*cspec)->flags)))
		bit_reset(2, &((*cspec)->flags));
	if (bit_get(1, &((*cspec)->flags)))
		bit_reset(3, &((*cspec)->flags));
}

void			parse_width(char **str, t_cspec **cspec)
{
	int			width;

	width = 0;
	(*cspec)->width_ast = 0;
	if (**str == '*')
	{
		(*cspec)->cspeclen += 1;
		(*cspec)->width_ast = 1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		(*cspec)->cspeclen += 1;
		width = width * 10 + (int)(**str - '0');
		(*str)++;
	}
	(*cspec)->width = width;
}

void			parse_precision(char **str, t_cspec **cspec)
{
	int			precision;

	precision = -1;
	(*cspec)->precision_ast = 0;
	if (**str == '.')
	{
		(*str)++;
		(*cspec)->cspeclen += 1;
		precision = 0;
		if (**str == '*')
		{
			(*cspec)->cspeclen += 1;
			(*cspec)->precision_ast = 1;
			(*str)++;
		}
		while (**str >= '0' && **str <= '9')
		{
			(*cspec)->cspeclen += 1;
			precision = precision * 10 + (int)(**str - '0');
			(*str)++;
		}
	}
	(*cspec)->precision = precision;
}

void			parse_size(char **str, t_cspec **cspec)
{
	(*cspec)->size = 'd';
	while (**str == 'l' || **str == 'h' || **str == 'L')
	{
		(*cspec)->cspeclen += 1;
		if (**str == 'L')
			(*cspec)->size = 'L';
		else if (**str == 'l')
		{
			if (*((*str) - 1) == 'l')
				(*cspec)->size = 'm';
			else
				(*cspec)->size = 'l';
		}
		else if (**str == 'h')
		{
			if (*((*str) - 1) == 'h')
				(*cspec)->size = 'i';
			else
				(*cspec)->size = 'h';
		}
		(*str)++;
	}
}

void			parse_type(char **str, t_cspec **cspec)
{
	(*cspec)->type = **str;
	(*cspec)->cspeclen += 1;
	(*str)++;
}
