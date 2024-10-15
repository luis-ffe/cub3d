# Cub3D

# cub3D

This project is a homage to the classic Wolfenstein 3D, the first FPS game ever created. It serves as an introduction to the concepts of ray-casting, allowing you to create a dynamic view inside a maze.
Inspired by the groundbreaking game Wolfenstein 3D, this project aims to replicate the core mechanics using ray-casting techniques. The objective is to create a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective using the MiniLibX library.

<img src="https://github.com/mjorgecruz/42_cub3d/blob/main/Screenshot%20from%202024-09-24%2011-39-06.png"/>

## Features

### Mandatory Features

- **First-Person View:**
- **Smooth Window Management:** The game handles window events smoothly, including changing focus and minimizing.
- **Textured Walls:** Different wall textures are displayed depending on their orientation (North, South, East, West).
- **Floor and Ceiling Colors:** Floor and ceiling are coloured using RGB values.
- **Basic Movements:**
  - **Arrow Keys:** Rotate the view left and right.
  - **W, A, S, D Keys:** Move through the maze.
  - **ESC Key:** Close the window and exit the program.
  - **Window Close Button:** Close the window and exit the program.

### Bonus Features

- **Wall Collisions:** Wall collision detection was added to prevent walking through walls.
- **Minimap System:** A minimap was added to show the player's location and surroundings.
- **Doors:** Doors that can be opened and closed were included.
- **Animated Sprites:** Included animated sprites for added visual interest.
- **Mouse Control:** Rotation of the view can be done using the mouse for a more intuitive experience.

## Configuration File Format

The configuration file (`.cub` format) specifies the map and textures and has to follow the following structure:

- **Textures:**
  - `NO path_to_north_texture`
  - `SO path_to_south_texture`
  - `WE path_to_west_texture`
  - `EA path_to_east_texture`
- **Colors:**
  - `F R,G,B` (Floor color)
  - `C R,G,B` (Ceiling color)
- **Map:**
  - `1` for walls, `0` for empty space, `N`, `S`, `E`, `W` for the player's starting position and orientation, `D` for doors and `F` for animated fires.

### Example

```plaintext
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

## How to run

1. Clone repository
    ```bash
    git clone git@github.com:luis-ffe/cub3d.git
    ```

2. Go inside project directory and run `make`
    ```bash
    cd 42_cub3d
    make bonus
    ```
3. Run `./cub3d_bonus {PATH_TO_MAP}`
     ```bash
    ./cub3d_bonus maps/valid/dungeon.cub
    ```
## Group Project : Credits

Jorge Cruz
Luis Carvalho

