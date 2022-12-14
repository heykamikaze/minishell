/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:13:18 by ksaffron          #+#    #+#             */
/*   Updated: 2021/10/09 18:20:04 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	a;

	src = (unsigned char *)s;
	a = (unsigned char)c;
	while (n > 0)
	{
		if (*src == a)
			return (src);
		src++;
		n--;
	}
	return (NULL);
}
