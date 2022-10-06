/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:03:02 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:10:15 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_newword(char *s, char c, size_t *i)
{
	char	*arr;
	size_t	len;
	size_t	start;

	len = 0;
	while (s[*i] == c && s[*i])
	{
		(*i)++;
	}
	start = *i;
	while (s[*i] != c && s[*i])
	{
		len++;
		(*i)++;
	}
	arr = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(arr, &s[start], len + 1);
	return (arr);
}

char	**ft_myfree(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	if (str)
		free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**string;
	size_t	word_count;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	string = ft_calloc(word_count + 1, sizeof(char *));
	if (string == NULL)
		return (NULL);
	while (i < word_count)
	{
		string[i] = ft_newword((char *)s, c, &j);
		if (string[i] == NULL)
		{
			return (ft_myfree(string));
		}
		i++;
	}
	string[i] = NULL;
	return (string);
}
