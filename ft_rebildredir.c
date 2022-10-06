/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rebildredir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:46 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrchr_upred(char *s, int c)
{
	size_t	i;
	char	*b;

	b = (char *)s;
	i = ft_strlen(s) + 1;
	ft_where_is_quot(' ', 1);
	while (i--)
	{
		if ((ft_where_is_quot(b[i], 0) == 0) && b[i] == (char) c)
		{
			return (1);
		}
	}
	return (0);
}

void	ft_create_l(t_struct *st, char *s, int index)
{
	int		i;
	int		len;
	char	*buffer;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == '<')
		{
			len = find_name_len(s, i, '<');
			buffer = ft_rebilder(st, i, len, index);
			st->commands[index - 1] = \
			ft_gnlstrjoin(st->commands[index - 1], buffer);
			if (buffer != NULL)
				free(buffer);
			if (st->commands[index - 1][0] == ';')
				st->commands[index - 1] = ft_skipsimic(st->commands[index - 1]);
			break ;
		}
		i--;
	}
}

void	ft_create_ll(t_struct *st, char *s, int index)
{
	int		i;
	int		len;
	char	*buffer;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			len = find_name_len(s, i, '<');
			buffer = ft_rebilder(st, i, len, index);
			st->commands[index - 1] = \
				ft_gnlstrjoin(st->commands[index - 1], buffer);
			if (buffer)
				free(buffer);
			if (st->commands[index - 1][0] == ';')
				st->commands[index - 1] = ft_skipsimic(st->commands[index - 1]);
			break ;
		}
		i++;
	}
}

void	ft_create_r(t_struct *st, char *s, int k)
{
	int		i;
	int		len;
	char	*buffer;
	int		f;

	i = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] == '>')
		{
			len = find_name_len(s, i, '>');
			buffer = ft_rebilder(st, i, len, k);
			if (st->commands[k + 1])
				free(st->commands[k + 1]);
			st->commands[k + 1] = buffer;
			while ((st->commands[k + 1][f] == '>'
				|| st->commands[k + 1][f] == ' ') && st->commands[k + 1][f])
				f++;
			open_file_h(st->commands[k + 1], \
				&st->commands[k + 1][f], 0);
			break ;
		}
		i++;
	}
}

void	ft_rebildredir(t_struct *st)
{
	int	i;

	i = 1;
	while (st->commands[i])
	{
		if (st->commands[i][0] != ';')
		{
			while (ft_strnstr(st->commands[i], "<<", \
				ft_strlen(st->commands[i])))
				ft_create_ll(st, st->commands[i], i);
			while (ft_strrchr_upred(st->commands[i], '<'))
				ft_create_l(st, st->commands[i], i);
			while (ft_strrchr_upred(st->commands[i], '>'))
				ft_create_r(st, st->commands[i], i);
		}
		if (st->commands[i + 1] && st->commands[i + 2])
			i += 2;
		if (st->commands[i + 1] != NULL)
			i++;
		if (st->commands[i + 1] != NULL)
			i++;
		else
			break ;
	}
}
