/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:54:13 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:58:39 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s2 || !s1)
		return (1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strchr_up(char *b, char *c)
{
	size_t	i;
	size_t	j;
	size_t	z;

	i = 0;
	if (!b)
		return (0);
	while (b[i])
	{
		j = i;
		z = 0;
		while (b[j])
		{
			if (b[j] != c[z])
				break ;
			j++;
			z++;
		}
		if (z == ft_strlen(c))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strelki(char **cmd)
{
	while (*cmd)
		if (!ft_strncmp(*cmd++, "<<", 2))
			return (1);
	return (0);
}

int	ft_set_in(t_struct *st, int in)
{
	close(in);
	st->pip.in = open("./libft/.tmp", O_RDONLY, 0777);
	return (st->pip.in);
}
