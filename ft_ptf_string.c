/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptf_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:23:56 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/16 17:23:59 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

t_cspec			*cspec_new(char **str)
{
	t_cspec		*new_cspec;

	if (!(new_cspec = (t_cspec *)malloc(sizeof(t_cspec))))
		return (NULL);
	*str += 1;
	new_cspec->cspeclen = 1;
	parse_flags(str, &new_cspec);
	parse_width(str, &new_cspec);
	parse_precision(str, &new_cspec);
	parse_size(str, &new_cspec);
	parse_type(str, &new_cspec);
	return (new_cspec);
}

t_list			*parse_string(char *str)
{
	t_cspec		*cspec;
	t_list		*all_cspecs;
	t_list		*list;

	all_cspecs = NULL;
	while (*str)
	{
		if (*str == '%')
		{
			if (!(cspec = cspec_new(&str)))
				return (NULL);
			if (!(list = ft_lstnew(cspec, SIZE)))
			{
				ft_memdel((void **)cspec);
				return (NULL);
			}
			ft_lstaddend(&all_cspecs, list);
			free(cspec);
		}
		else
			str++;
	}
	return (all_cspecs);
}

int				print_percent(char **str, t_list **list)
{
	int			i;

	i = CSPEC->width - 1;
	if (bit_get(0, &CSPEC->flags))
	{
		write(1, "%", 1);
		while (i-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (i-- > 0)
			write(1, (bit_get(2, &CSPEC->flags) ? "0" : " "), 1);
		write(1, "%", 1);
	}
	(*str) += CSPEC->cspeclen;
	i = CSPEC->width > 0 ? CSPEC->width : 1;
	*list = (*list)->next;
	return (i);
}

int				print_char(char **str, t_list **list, va_list args)
{
	char		c;
	int			i;

	c = va_arg(args, int);
	i = CSPEC->width - 1;
	if (bit_get(0, &CSPEC->flags))
	{
		write(1, &c, 1);
		while (i-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (i-- > 0)
			write(1, (bit_get(2, &CSPEC->flags) ? "0" : " "), 1);
		write(1, &c, 1);
	}
	(*str) += CSPEC->cspeclen;
	i = CSPEC->width > 0 ? CSPEC->width : 1;
	*list = (*list)->next;
	return (i);
}

int				print_string(char **str, t_list **list, va_list args)
{
	char		*s;
	int			i;

	s = CSPEC->precision < 0 ? ft_strdup(va_arg(args, char *)) :
	ft_strsub(va_arg(args, char *), 0, CSPEC->precision);
	if (!s)
		s = ft_strsub("(null)", 0, CSPEC->precision < 0 ? 6 : CSPEC->precision);
	i = CSPEC->width - ft_strlen(s);
	if (bit_get(0, &CSPEC->flags))
	{
		ft_putstr(s);
		while (i-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (i-- > 0)
			write(1, (bit_get(2, &CSPEC->flags) ? "0" : " "), 1);
		ft_putstr(s);
	}
	i = CSPEC->width < (int)ft_strlen(s) ? ft_strlen(s) : CSPEC->width;
	(*str) += CSPEC->cspeclen;
	*list = (*list)->next;
	free(s);
	return (i);
}
