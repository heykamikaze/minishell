/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenjami <nbenjami@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:51:12 by ksaffron          #+#    #+#             */
/*   Updated: 2022/07/21 10:44:26 by nbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *arg, t_struct *st)
{
	char	**splited;
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	splited = ft_split_wquots(arg);
	if (!ft_strcmp(splited[i], "-n"))
	{
		i++;
		flag = 1;
	}
	while (splited[i])
	{	
		ft_putstr(splited[i]);
		i++;
		if (splited[i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	(void)st;
	exit(0);
}
