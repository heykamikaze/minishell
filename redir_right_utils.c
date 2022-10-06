/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_right_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaffron <ksaffron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:53:52 by ksaffron          #+#    #+#             */
/*   Updated: 2022/03/06 13:53:54 by ksaffron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*make_array(char **argv)
{
	int	*files;
	int	i;
	int	acc;

	i = -1;
	acc = 0;
	while (argv[++i])
	{
		if (!ft_strncmp(argv[i], ">>", 2))
			acc++;
		else if (!ft_strncmp(argv[i], ">", 1))
			acc++;
	}
	files = malloc((acc + 1) * sizeof(int));
	if (!files)
		ft_error(NULL, 1);
	return (files);
}

int	open_file_h(char *redir, char *file, int flag)
{
	int	fd;

	fd = -2;
	if (!ft_strncmp(redir, ">>", 2) && file)
		fd = open(file, \
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (!ft_strncmp(redir, ">", 1) && file)
		fd = open(file, \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!flag)
		close(fd);
	return (fd);
}

int	*ft_open_files(int n, char **argv)
{
	int	*files;
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (n > 1)
	{
		files = make_array(argv);
		if (!files)
			return (NULL);
	}
	while (n > 1 && argv[++i])
		files[count++] = open_file_h(argv[i], argv[i + 1], 1);
	if (!files)
		return (NULL);
	return (files);
}
