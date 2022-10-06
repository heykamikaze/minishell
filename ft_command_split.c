/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:52:33 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_noth(void)
{
	char	*string;

	string = malloc(sizeof(char) * 2);
	if (!string)
		ft_error(NULL, 1);
	string[0] = ';';
	string[1] = '\0';
	return (string);
}

int	add_pipe_helper(t_struct *st, char **newcom, int i, int j)
{
	while (st->splited[i])
	{
		newcom[j++] = ft_add_noth();
		newcom[j++] = st->splited[i];
		newcom[j++] = ft_add_noth();
		if (st->splited[i + 1] != NULL)
		{
			newcom[j] = malloc(sizeof(char) * 2);
			if (newcom[j] == NULL)
				return (ft_error(st, 1));
			newcom[j][0] = '|';
			newcom[j][1] = '\0';
			j++;
		}
		i++;
	}
	newcom[j] = NULL;
	return (0);
}

int	ft_add_pipe(t_struct *st)
{
	char	**newcom;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (st->splited[i])
		i++;
	len = (i + i - 1) + i * 2;
	newcom = malloc(sizeof(char *) * (len + 1));
	if (newcom == NULL)
		return (ft_error(st, 1));
	len = i;
	i = 0;
	j = 0;
	add_pipe_helper(st, newcom, i, j);
	if (st->commands)
		ft_myfree(st->commands);
	st->commands = newcom;
	return (1);
}
