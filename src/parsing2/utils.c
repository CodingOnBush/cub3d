#include "../inc/cub3d.h"

int	ft_atoicolor(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		return (ft_err("Sign before color value are not allowed", -1));
	if (str[i] == '0' && str[i + 1] != '\0')
		return (ft_err("Invalid color value", -1));
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - 48);
		if (res > 255)
			return (ft_err("Overflow of color value", -1));
		i++;
	}
	if (str[i] != '\0')
		return (ft_err("Invalid color value", -1));
	return (res);
}

int	ft_is_datafull(t_env *env)
{
	if (!env)
		return (NO);
	if (env->data.so.path == NULL || env->data.no.path == NULL
		|| env->data.ea.path == NULL || env->data.we.path == NULL)
		return (NO);
	if (env->data.floor.r == -1 || env->data.floor.g == -1
		|| env->data.floor.b == -1)
		return (NO);
	if (env->data.ceil.r == -1 || env->data.ceil.g == -1
		|| env->data.ceil.b == -1)
		return (NO);
	return (YES);
}
