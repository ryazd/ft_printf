/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_printable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluthor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:54:34 by hluthor           #+#    #+#             */
/*   Updated: 2019/12/16 19:50:14 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

int				ft_strlen_non(char *s)
{
	int			i;
	int			pos;

	pos = 0;
	i = 0;
	while (s[pos])
	{
		if (s[pos] >= 0 && s[pos] <= 31)
			i += 4;
		pos++;
		i++;
	}
	return (i);
}

char			*non_print_mas(void)
{
	char		*mas;
	char		*s1;

	mas = ft_strjoin("", "NULSCHSTXETXEOTENQACKBELBS HT LF VT FF CR SO SI ");
	s1 = mas;
	mas = ft_strjoin(mas, "DLEDC1DC2DC3DC4NAKSYNETBCANEM SUBESCFS GS RS US");
	free(s1);
	return (mas);
}

int				ft_stradd_non(char **str, int pos2, int i)
{
	char		*mas;
	int			j;

	i *= 3;
	j = 0;
	mas = non_print_mas();
	(*str)[pos2] = '<';
	pos2++;
	while (j < 3)
	{
		if (mas[i] != ' ')
		{
			(*str)[pos2] = mas[i];
			pos2++;
		}
		i++;
		j++;
	}
	(*str)[pos2] = '>';
	free(mas);
	return (pos2);
}

char			*str_non_print(va_list args)
{
	char		*str;
	char		*s;
	int			pos1;
	int			pos2;
	char		*s_free;

	pos1 = 0;
	pos2 = 0;
	s = va_arg(args, char *);
	if (!(str = (char *)malloc(ft_strlen_non(s) + 1)))
		return (NULL);
	while (s[pos1])
	{
		if (s[pos1] >= 0 && s[pos1] <= 31)
			pos2 = ft_stradd_non(&str, pos2, s[pos1]);
		else
			str[pos2] = s[pos1];
		pos2++;
		pos1++;
	}
	str[pos2] = '\0';
	s_free = str;
	str = ft_strjoin(str, "<NUL>");
	free(s_free);
	return (str);
}

int				print_non_printable(char **str, t_list **list, va_list args)
{
	char		*s;
	int			i;

	s = CSPEC->precision < 0 ? str_non_print(args) :
		ft_strsub(str_non_print(args), 0, CSPEC->precision);
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
