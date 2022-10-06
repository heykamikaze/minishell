/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:51:46 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 14:50:42 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_var(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str))
		if (*str != '_')
			return (0);
	while (str && *str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	ft_delelem(t_list **content)
{
	t_list	*current;
	t_list	*next;

	current = *content;
	next = (*content)->next;
	current->next = next->next;
	ft_lstdelone(next, free);
	return (0);
}

int	ft_unset_print_err(char **splited, int i)
{
	if (!check_name_var(splited[i]))
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(splited[i], 2);
		ft_putstr_fd("': ", 2);
		ft_putstr_fd("not a valid identifier\n", 2);
		ft_myfree(splited);
		return (0);
	}
	return (1);
}

void	ft_inset_helper(char *splited_i, int len, t_struct *st)
{
	t_list	*dup;
	char	*tmp;

	dup = st->content;
	tmp = ft_strjoin(splited_i, "=");
	while (dup->next)
	{
		if (!ft_strncmp(dup->next->content, tmp, len + 1))
		{
			ft_delelem(&(dup));
			break ;
		}
		dup = dup->next;
	}
	free(tmp);
}

int	ft_unset(char *var, t_struct *st)
{
	char	**splited;
	int		i;
	int		len;

	splited = ft_split_wquots(var);
	i = 1;
	len = ft_strlen(splited[i]);
	while (splited[i])
	{
		if (!ft_unset_print_err(splited, i))
			return (1);
		ft_inset_helper(splited[i], len, st);
		i++;
		len = ft_strlen(splited[i]);
	}
	set_envp(st);
	ft_myfree(splited);
	return (0);
}
