/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:22:36 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:22:36 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>

static void		unset_env(t_seq *seq)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], seq->args, ft_strlen(seq->args)) == 0)
		{
			ft_strclr(environ[i]);
			environ[i] = environ[i + 1];
			i++;
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	return ;
}

static void		set_env(t_seq *seq)
{
	int				i;
	int				check;
	extern char		**environ;

	i = 0;
	check = 0;
	while (seq->args[i])
	{
		if (seq->args[i] == '=')
			check++;
		i++;
	}
	if (check)
	{
		while (environ[i])
			i++;
		environ[i] = seq->args;
		environ[i + 1] = 0;
	}
	return ;
}

static void		ft_env(t_seq *seq)
{
	extern char	**environ;
	int		i;

	i = 0;
	seq->file = 0;
	while (environ[i])
	{
		ft_putstr(environ[i]);
		ft_putstr("\n");
		i++;
	}
}

void			do_exit(t_seq *seq)
{
	seq = NULL;
	ft_restore();
	ft_cleaner(NULL, NULL, 1);
	exit(0);
}

t_handler		ft_isfunc(char *cmd)
{
	int				i;


	t_builtin_cmd	builtins[] =
	{
		{"exit", do_exit},
		{"cd", ft_cd},
		{"env", ft_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"echo", ft_echo},
		{"read", ft_read},
		{"set", ft_set},
		{"unset", ft_unset},
		{NULL, NULL}
	};

	i = 0;
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(cmd, builtins[i].name) == 0)
			 return (builtins[i].handler);
		i++;
	}
	return (NULL);
}
