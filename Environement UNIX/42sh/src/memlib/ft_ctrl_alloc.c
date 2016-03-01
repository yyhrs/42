
#include <stdlib.h>
#include "../libft.h"
#include "../header.h"

void	*ft_malloc(int s)
{
	void	*result;

	result = malloc(s);
	if (!result)
	{
		ft_putstr_fd("Error with memory allocation\n", 2);
		return (NULL);
	}
	else
		return (result);
}

void	ft_free(void *var)
{
	if (var)
		free(var);
	var = NULL;
	return ;
}

void	ft_free_data_hash(t_data **var)
{
	int		i;
	t_data	*tmp;

	i = -1;
	while (var[++i])
	{
		if (var[i])
		{
			ft_free(var[i]->cmd);
			ft_free(var[i]->path);
			tmp = var[i];
			while(var[i]->right)
			{
				var[i] = var[i]->right;
				ft_free(tmp);
				tmp = var[i];
				ft_free(var[i]->cmd);
				ft_free(var[i]->path);
			}
		}
		ft_free(var[i]);
	}
	ft_free(var);
	return ;
}
