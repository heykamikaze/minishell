/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:02:56 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 15:08:23 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrchr_deep(char *s, int c)
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
			return (i);
		}
	}
	return (0);
}

void	ft_last_redd(t_struct *st, char *s, int index)
{
	int	j;

	j = -1;
	j = ft_strrchr_deep(s, '<');
	if (j != 0)
	{
		if (s[j - 1] == '<')
			st->last_r[index] = 2;
		else
			st->last_r[index] = 1;
	}
	else
		st->last_r[index] = 1;
}

void	ft_last_red(t_struct *st, char **s)
{
	int	iinc[3];

	iinc[0] = 0;
	iinc[2] = 0;
	while (s[iinc[0]])
	{
		iinc[2]++;
		iinc[0]++;
	}
	iinc[0] = 0;
	iinc[1] = 0;
	st->last_r = malloc((sizeof(int) + 1) * iinc[2] / 2);
	if (st->last_r == NULL)
		ft_error(st, 1);
	while (s[iinc[0]])
	{
		while (s[iinc[0]] && (s[iinc[0]][0] == ';' || s[iinc[0]][0] == '|'))
			iinc[0]++;
		if (!s[iinc[0]])
			break ;
		ft_last_redd(st, s[iinc[0]], iinc[1]);
		iinc[0]++;
		iinc[1]++;
	}
}

int	ft_getlen(char *splited)
{
	int		len;

	len = 0;
	while (splited && splited[len] && splited[len] != '=')
		len++;
	return (len);
}

int	ft_changevar(char **splited, t_list **vars, int len)
{
	(void)len;
	free((*vars)->content);
	(*vars)->content = ft_strdup(*splited);
	return (0);
}
