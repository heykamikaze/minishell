/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:51:19 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 15:04:57 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_envp(t_struct *st)
{
	int		count;
	char	**new_env;
	t_list	*dup;
	int		i;

	count = ft_lstsize(st->content);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (ft_error(st, 1));
	new_env[count] = NULL;
	dup = st->content;
	i = 0;
	while (dup)
	{
		new_env[i++] = ft_strdup(dup->content);
		dup = dup->next;
	}
	if (st->env)
		ft_myfree(st->env);
	st->env = new_env;
	return (1);
}

void	ft_getting_env(t_struct *st)
{
	t_list	*dup;

	dup = st->content;
	while (dup)
	{
		ft_putstr(dup->content);
		ft_putchar_fd('\n', 1);
		dup = dup->next;
	}
	exit(0);
}
