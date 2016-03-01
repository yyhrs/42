/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:22:17 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:22:17 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../header.h"
#include "../libft.h"

static void	ft_change_path(char **env)
{
	char	buf[1024];
	int		i;
	int		j;

	i = 0;
	while (env[i] && ft_strncmp("OLDPWD=", env[i], 7))
		i++;
	j = 0;
	while (env[j] && ft_strncmp("PWD=", env[j], 4))
		j++;
	if (env[i] && env[j])
	{
		free(env[i]);
		env[i] = ft_strjoin(ft_strdup("OLDPWD="), env[j] + 4);
	}
	if (env[j])
	{
		buf[1023] = '\0';
		getcwd(buf, 1023);
		free(env[j]);
		env[j] = ft_strjoin(ft_strdup("PWD="), buf);
	}
}

static void	ft_case(t_seq *seq, char **env, int i)
{
	if (seq->args[0] == '~')
	{
		i = 0;
		while (env[i] && ft_strncmp("HOME=", env[i], 5))
			i++;
		if (env[i])
		seq->args = ft_strjoin(ft_strdup(env[i] + 5),
								ft_strjoin(ft_strdup("/"), seq->args + 1));
	}
	else if (seq->args[0] == '-' && !seq->args[1])
	{
		i = 0;
		while (env[i] && ft_strncmp("OLDPWD=", env[i], 7))
			i++;
		if (env[i])
			seq->args = env[i] + 7;
	}
	else if (!seq->args)
	{
		i = 0;
		while (env[i] && ft_strncmp("HOME=", env[i], 5))
			i++;
		if (env[i])
			seq->args = ft_strdup(env[i] + 5);
	}
}

void		ft_cd(t_seq *seq)
{
	extern char	**environ;

	ft_case(seq, environ, 0);
	ft_putstr_fd(seq->args, 2);
	if (chdir(seq->args) == -1)
	{
		ft_putstr_fd("cd: no such directory or permission denied: \n", 2);
		ft_putstr_fd(seq->args, 2);
	}
	else
		ft_change_path(environ);
}
