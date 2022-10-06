/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_check_reddir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:51:52 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_redd(char *s, int i)
{
	int	j;

	ft_where_is_quot(' ', 1);
	while (s[i + 1] == ' ' && s[i + 1])
		i++;
	j = i + 1;
	if (s[i + 1] == '>' || s[i + 1] == '|'
		|| s[i + 1] == '<' || !s[i + 1])
		return (0);
	if (ft_isdigit(s[j]) && s[j - 1] == '>' && s[j + 1] == '>')
		return (0);
	return (1);
}

int	ft_check_reddir(t_struct *st)
{
	int	i;

	i = 0;
	while (st->line[i])
	{
		if (st->line[i] == '>' || st->line[i] == '<')
		{
			if ((st->line[i + 1] == '>' && st->line[i] == '>')
				|| (st->line[i + 1] == '<' && st->line[i] == '<'))
			{
				if (err_redd(st->line, i + 1) == 0)
					return (1);
				i++;
			}
			else
			{
				if (err_redd(st->line, i) == 0)
					return (1);
			}
		}
		i++;
	}
	return (0);
}
