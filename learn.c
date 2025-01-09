// #include "so_long.h"


// #include <mlx.h>

// int	main(void)
// {
//     void    *mlx;
//     void    *win;
//     void    *img;
//     char    *relative_path = "./image.xpm";
//     int     img_width;
//     int     img_height;

//     mlx = mlx_init();

//     win = mlx_new_window(mlx, 2000, 2000, "Image in Window");
//     img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
//     if (img == NULL)
//     {
//         mlx_destroy_window(mlx, win);
//         return (1);
//     }
//     mlx_put_image_to_window(mlx, win, img, 100, 100);
//     mlx_loop(mlx);

//     return (0);
// }



