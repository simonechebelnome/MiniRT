#include "../includes/minirt.h"

char	**free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	return (split);
}

int	split_check(char **split, int max)
{
	int	i;
	int	j;

	i = 1;
	if (!max)
		return (-1);
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != ',' && split[i][j]
				!= '.' && split[i][j] != '-' && i < max)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	char_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_vector	get_normal(t_global *core, t_vector point)
{
	t_vector	normal;

	if (core->obj->id == 4 || core->obj->id == 3 || core->obj->id == 2)
		normal = vec_normalize(core->obj->dir);
	else if (core->obj->id == 6)
		normal = cy_normal(core->obj, point);
	else
		normal = vec_normalize(vec_sub(point, core->obj->ori));
	return (normal);
}

t_object	*new_object(t_object *obj, t_global *core)
{
	t_object	*new_obj;

	new_obj = ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		exit_program("Errore nel malloc", core);
	ft_memcpy(new_obj, obj, sizeof(t_object));
	return (new_obj);
}
