#include "../includes/minirt.h"

int	scroll_press(int button, int x, int y, t_global *core)
{
	(void)x;
	(void)y;
	if (button == 1)
		core->scroll = 1;
	return (1);
}

int	scroll_release(int button, int x, int y, t_global *core)
{
	(void)x;
	(void)y;
	if (button == 1)
		core->scroll = 0;
	return (1);
}
