/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:41:45 by gshamika          #+#    #+#             */
/*   Updated: 2019/11/05 16:09:45 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

void			free_join(char **integer, char *symbol, int end)
{
	char		*tmp;

	tmp = *integer;
	if (end)
		*integer = ft_strjoin(*integer, symbol);
	else
		*integer = ft_strjoin(symbol, *integer);
	free(tmp);
}

void			free_list(t_list **list)
{
	t_list		*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->content);
		temp->next = NULL;
		free(temp);
	}
	free(*list);
	*list = NULL;
}

int				ft_printf(const char *str, ...)
{
	va_list		args;
	t_list		*cspecs;
	t_list		*start;
	int			printed;

	if (!str)
		return (0);
	cspecs = parse_string((char *)str);
	start = cspecs;
	va_start(args, str);
	printed = print_all_cspecs((char **)&str, args, &cspecs);
	va_end(args);
	free_list(&start);
	return (printed);
}
