
valgrind --leak-check=full --show-leak-kinds=all ./cub3D ./map.cub 

opt 1: map file doesn't allow space character inside map - check with floodfill. -> Done it
opt 2: map file has space character inside map 
-> check if it is border with wall -> ok, if not -> no good