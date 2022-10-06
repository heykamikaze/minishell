/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:04:53 by ksaffron          #+#    #+#             */
/*   Updated: 2021/10/09 18:50:49 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*a;
	char	b;

	a = (char *)s + ft_strlen(s);
	b = (char)c;
	while (a >= s)
	{
		if (*a == b)
			return (a);
		a--;
	}
	return (0);
}
