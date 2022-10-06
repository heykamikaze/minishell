/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rebildredir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:41 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	helper(char *s, int *i)
{
	int	j;

	j = 0;
	while (s[*i] == ' ' && s[*i])
	{
		j++;
		(*i)++;
	}
	return (j);
}

void	ft_skipp(char *s, int *i, int *j)
{
	if (s[*i] == 34)
	{
		while (s[*i] != 34 && s[*i])
		{
			(*j)++;
			(*i)++;
		}
	}
	else if (s[*i] == 39)
	{
		while (s[*i] != 39 && s[*i])
		{
			(*j)++;
			(*i)++;
		}
	}
	else if ((ft_isalnum(s[*i]) || s[*i] == '.'))
	{
		while ((ft_isalnum(s[*i]) || s[*i] == '.') && s[*i])
		{
			(*j)++;
			(*i)++;
		}
	}
}

int	find_name_len(char *s, int i, char c)
{
	int	j;

	j = 0;
	while (s[i] == c)
	{
		i++;
		j++;
	}
	j += helper(s, &i);
	ft_skipp(s, &i, &j);
	return (j);
}

char	*ft_skipsimic(char *s)
{
	char	*tmp;

	tmp = ft_substr(s, 1, ft_strlen(s));
	if (s != NULL)
		free(s);
	return (tmp);
}

char	*ft_rebilder(t_struct *st, int i, int len, int index)
{
	char	*newline;
	char	*modif;
	char	*tmp;
	char	*tmp2;

	modif = ft_substr(st->commands[index], 0, i);
	newline = ft_substr(st->commands[index], i, len);
	tmp = modif;
	tmp2 = ft_substr(st->commands[index], i + len, \
		(ft_strlen(st->commands[index]) - len - i));
	modif = ft_strjoin(modif, tmp2);
	if (st->commands[index] != NULL)
		free(st->commands[index]);
	st->commands[index] = modif;
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
	return (newline);
}
