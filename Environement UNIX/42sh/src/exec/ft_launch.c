/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 17:22:28 by erobert           #+#    #+#             */
/*   Updated: 2014/02/18 17:55:02 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../header.h"
#include "../libft.h"

void			ft_launch(int do_fork, t_seq *seq)
{
	extern char	**environ;
	pid_t		father;
	char		*tmp;

	if (ft_gotredirection(seq, seq->args))
	{
		ft_redirection(seq);
		return ;
	}
	if (seq->path == NULL)
	{
		seq->func(seq);
		return ;
	}
	tmp = ft_strdup(seq->cmd);
	tmp = ft_strjoin(tmp, " ");
	tmp = ft_strjoin(tmp, seq->args);
	seq->exec_tab = ft_strsplit(tmp, ' ');
	free(tmp);
	if (!do_fork)
		execve(seq->path, seq->exec_tab, environ);
	if ((father = fork()) == 0)
		execve(seq->path, seq->exec_tab, environ);
	else
		waitpid(0, NULL, 0);
}
