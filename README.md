*This project has been created as part of the 42 curriculum by rdamasce, mrosembe.*

# cub3D

## Description

cub3D is a first-person 3D maze renderer inspired by Wolfenstein 3D, written
in C with the MiniLibX. It reads a scene description file (`.cub`) containing
the wall textures, the floor and ceiling colors and a 2D map, and renders it in
real time using **ray-casting**: for every column of the screen a ray is cast
through the map grid (DDA algorithm) to find the closest wall and draw a
vertical textured slice whose height depends on the wall distance.

Features (mandatory part):

- Different wall textures for North, South, East and West faces.
- Configurable floor and ceiling colors.
- `W` `A` `S` `D` to move, `←` `→` to look around.
- `ESC` or the window's red cross to quit cleanly.
- Strict `.cub` validation: any configuration error prints `Error\n` followed
  by an explicit message.

## Instructions

### Requirements (Linux)

```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev zlib1g-dev
```

### Setup

```bash
# 1. MiniLibX
git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux

# 2. libft: copy your libft into ./libft (see libft/README.md)
```

### Build

```bash
make        # builds ./cub3D
make clean  # removes object files
make fclean # removes object files and the binary
make re     # full rebuild
```

### Run

```bash
./cub3D maps/valid/subject.cub
```

### Project layout

```
includes/        headers (structs.h is the parsing <-> execution contract)
src/parsing/     .cub reading and validation   -> fills t_scene
src/execution/   MiniLibX, raycasting, input   -> uses t_scene
src/utils/       shared helpers
maps/valid/      maps that must open
maps/invalid/    maps that must print "Error"
textures/        .xpm wall textures
docs/            internal documentation (pt-BR)
```

## Resources

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX documentation (harm-smits)](https://harm-smits.github.io/42docs/libs/minilibx)
- [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux)
- [A first-person engine in 265 lines](https://www.playfuljs.com/a-first-person-engine-in-265-lines/)
- [Permadi — Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

### AI usage

AI was used to generate the initial project skeleton (folder structure,
Makefile, headers and empty function stubs with comments), the test maps,
the placeholder textures and the internal documentation in `docs/`.
<!-- TODO: describe any other AI usage during implementation. -->
