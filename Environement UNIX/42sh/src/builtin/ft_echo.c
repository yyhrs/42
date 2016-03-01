
#include "../header.h"
#include "../libft.h"
#include <termcap.h>
#include <termios.h>

/*
NOM
echo - Afficher une ligne de texte.

SYNOPSIS
echo [-neE] [message ...]

echo {--help,--version}

DESCRIPTION
Cette page de manuel documente la version GNU de echo.

La plupart des shells ont une commande intégrée ayant le même nom et les mêmes fonctionnalités.

echo écrit chaque message sur la sortie standard, avec une espace entre chacun d'eux, et un saut de ligne après le dernier.

OPTIONS
-n
Ne pas effectuer le saut de ligne final.
-e
Interpréter les séquences de caractères précédées d'un backslash '\' suivantes :
\a
alerte (sonnerie)
\b
retour en arrière d'un caractère
\c
supprimer le saut de ligne final
\f
saut de page
\n
saut de ligne
\r
retour chariot
\t
tabulation horizontale
\v
tabulation verticale
\\
backslash
\nnn
le caractère de code ASCII nnn (en octal)
-E
Désactiver les interprétations des séquences spéciales.
OPTIONS GNU
Quand la version GNU de echo est appelée avec exactement un argument, les options suivantes sont reconnues :

--help
Afficher un message d'aide sur la sortie standard et se terminer normalement.
--version
Afficher un numéro de version sur la sortie standard et se terminer normalement.
*/

static void			ft_echo_escape_char(char c)
{
	if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar_term);
	else if (c == 't')
		ft_putstr("\t");
	else if (c == 'v')
		ft_putchar('\v');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'a')
		ft_putchar('\a');
	else if (c == '0')
		ft_putchar('\0');
	else if (c == '"')
		ft_putchar('"');
	else if (c == '$')
		ft_putchar('$');
	else if (c == '\\')
		ft_putchar('\\');
	else
	{
		ft_putchar('\\');
		ft_putchar(c);
	}
}

static void			ft_echo_display(char *s, int op_E)
{
	char	c;

	c = 0;
	while (*s)
	{
		if (CHAR_S(*s) && !c)
		{
			c = *s;
			s++;
		}
		if (*s == '\\' && !op_E)
		{
			s++;
			ft_echo_escape_char(*s);
		}
		else if (*s != c)
			ft_putchar((*s));
		if (*s == c)
			c = 0;
		s++;
	}
}

void				ft_echo(t_seq *seq)
{
	int				op_E;
	int				op_n;
	int				i;

	i = op_E = op_n = 0;
	if (seq->args[0] == '-' && seq->args[1])
	{
		while (seq->args[i] != ' ')
		{
			if (seq->args[i] == 'E')
				op_E = 1;
			else if (seq->args[i] == 'e')
				op_E = 0;
			if (seq->args[i] == 'n')
				op_n = 1;
			i++;
		}
	}
	ft_echo_display(&(seq->args[i]), op_E);
	if (!op_n)
		ft_putchar('\n');
}
