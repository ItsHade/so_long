#include "../include/so_long.h"

// int main(void)
// {
// 	int width = 32;
// 	int height = 32;

// 	void *mlx_ptr;
// 	void *win_ptr;
// 	void *img_ptr;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 1280, 720, "Image XPM");
// 	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/player.xpm", &width, &height);
// 	if (img_ptr == NULL)
// 	{
//         ft_putstr("il y a un probleme!\n");
// 		return (1);
// 	}
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
// 	mlx_loop(mlx_ptr);
// 	// free(img_ptr);
// }


int main(void)
{
	int a = 156;
	ft_putnbr(ft_intlen(a));
	ft_putchar('\n');
	ft_putstr(ft_itoa(a));
}