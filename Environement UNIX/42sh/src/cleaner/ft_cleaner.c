/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:22:51 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:22:51 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

void			ft_clean_seq(t_seq *seq)
{
	int	i;

	while (seq)
	{
		i = 0;
		ft_free(seq->cmd);
		ft_free(seq->args);
		// if (seq->extra)
		// 	free(seq->extra);
		if (seq->exec_tab)
		{
			while (seq->exec_tab[i])
			{
				ft_free(seq->exec_tab[i]);
				i++;
			}
			ft_free(seq->exec_tab);
		}
		seq = seq->next;
	}
	return ;
}

static void		ft_clean_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		ft_free(cmd->origin);
		ft_free(cmd->clean);
		if (cmd->seq)
			ft_clean_seq(cmd->seq);
		cmd = cmd->next;
	}
	return ;
}

static void		ft_do_clean(char **environ, t_data **path, t_cmd *cmd)
{
	// int	i;


	if (path)
		ft_free_data_hash(path);
	environ = NULL;
	// i = 0;
	// while (environ[i])
	// {
	// 	ft_free(environ[i]);
	// 	i++;
	// }
	ft_clean_cmd(cmd);
	return ;
}

void			ft_cleaner(t_data **path, t_cmd *cmd, int value)
{
	static t_data	**save_path = NULL;
	static t_cmd	*save_cmd = NULL;
	extern char		**environ;

	if (value == 0)
	{
		if (path && !save_path)
			save_path = path;
		if (cmd && !save_cmd)
			save_cmd = cmd;
	}
	else
		ft_do_clean(environ, save_path, save_cmd);
	return ;
}
