/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:54:19 by gshamika          #+#    #+#             */
/*   Updated: 2019/12/03 13:12:37 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static void	free_join(char **integer, char *symbol, int end)
{
	char	*tmp;

	tmp = *integer;
	if (end)
		*integer = ft_strjoin(*integer, symbol);
	else
		*integer = ft_strjoin(symbol, *integer);
	free(tmp);
}

char		*ft_ldtoa(long double n, int precision)
{
	char	*result;
	char	*f;

	n = n + (n < 0 ? -0.5 : 0.5) * (ft_pow(0.1, precision));
	n = n < 0 ? -n : n;
	result = ft_lltoa((long long)n);
	n = n - (long long)n;
	if (precision > 0)
	{
		free_join(&result, ".", 1);
		while (precision > 0)
		{
			n *= 10;
			f = ft_lltoa((int)n);
			free_join(&result, f, 1);
			free(f);
			n -= (int)n;
			precision--;
		}
	}
	return (result);
}
