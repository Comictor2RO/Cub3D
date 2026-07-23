# Cub3D

A first-person raycasting engine written in C, inspired by the classic *Wolfenstein 3D*. Cub3D renders a pseudo-3D world from a simple 2D grid map using the DDA (Digital Differential Analysis) raycasting algorithm, with textured walls, a live minimap, and smooth mouse-and-keyboard movement.

This is a project, built on top of the [MiniLibX](https://github.com/42Paris/minilibx-linux) graphics library and a custom `libft`.

---

## Features

- **DDA raycasting engine** — casts one ray per screen column to project a textured 3D scene.
- **Textured walls** — separate textures for the North, South, West and East faces, loaded from `.xpm` files.
- **Configurable floor and ceiling colors** — set via RGB triplets in the map file.
- **Fish-eye correction** — uses perpendicular wall distance to keep vertical lines straight.
- **Live 2D minimap** — shows the map, the player, and the cast rays in real time.
- **Fluid controls** — WASD strafing/movement, mouse look, and arrow-key rotation.
- **Robust map parser** — strict validation of textures, colors, and map closure with clear error messages.
- **Clean memory management** — validated with Valgrind (`valgrind.supp` provided for MiniLibX leaks).

---

## Requirements

- A Linux environment (MiniLibX is built for X11).
- `cc` / `gcc`, `make`
- X11 development libraries: `libxext-dev`, `libx11-dev`
- The math library (`-lm`)

---

## Build

```bash
make        # build the cub3D executable
make clean  # remove object files
make fclean # remove object files and the executable
make re     # full rebuild
```

The `Makefile` automatically builds the bundled `libft` and `minilibx-linux` before linking. Compilation uses `-Wall -Wextra -Werror`.

---

## Usage

```bash
./cub3D <map.cub>
```

The program takes exactly one argument: a scene description file with the `.cub` extension.

```bash
./cub3D maps/simple.cub
```

### Controls

| Input          | Action                          |
| -------------- | ------------------------------- |
| `W` / `S`      | Move forward / backward         |
| `A` / `D`      | Strafe left / right             |
| `←` / `→`      | Rotate the camera               |
| Mouse          | Look around (rotate the view)   |
| `Esc`          | Quit                            |
| Window close   | Quit                            |

---

## Map File Format (`.cub`)

A scene file describes the textures, colors, and the map layout.

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 135,206,235

1111111111
1000100001
1000N00001
1000100001
1000000001
1000000001
1000000001
1111111111
```

### Elements

| Identifier | Meaning                                  |
| ---------- | ---------------------------------------- |
| `NO`       | Path to the North wall texture (`.xpm`)  |
| `SO`       | Path to the South wall texture (`.xpm`)  |
| `WE`       | Path to the West wall texture (`.xpm`)   |
| `EA`       | Path to the East wall texture (`.xpm`)   |
| `F`        | Floor color as `R,G,B` (0–255 each)      |
| `C`        | Ceiling color as `R,G,B` (0–255 each)    |

### Map symbols

| Symbol      | Meaning                                     |
| ----------- | ------------------------------------------- |
| `1`         | Wall                                        |
| `0`         | Empty (walkable) space                      |
| `N/S/E/W`   | Player spawn position and initial direction |
| ` ` (space) | Void (treated as a wall for collisions)     |

### Validation rules

The parser rejects a scene unless:

- The file has a `.cub` extension.
- Each texture identifier appears **exactly once**, the path exists on disk, and it is an `.xpm` file.
- Colors are strictly `R,G,B` with exactly 3 components, each in the range `0–255`.
- The map contains **exactly one** spawn character (`N`, `S`, `E`, or `W`).
- The map is **closed**: every walkable cell is surrounded on all four sides, with no gaps opening to the void or the outside.

---

## How It Works

Cub3D turns a flat 2D grid into a 3D view in two stages.

### 1. Parsing

`parse_cub_file()` reads the scene line by line and dispatches each line through `process_line()`:

- texture lines → `parse_textures()`
- color lines → `parse_color_line()` (converted to a packed hex value via `rgb_to_hex()`)
- map lines → `add_map_line()`

Once every element is present (`check_all_elements()`), the map is normalized to a uniform width (`normalize_map()`), the spawn is located and validated for uniqueness (`find_player()`), and closure is verified (`validate_map()`). Finally, `init_player_from_map()` converts the grid spawn into world coordinates and direction/plane vectors for the engine.

See [PARSING.md](PARSING.md) for a detailed walkthrough.

### 2. Raycasting

For each screen column `x`, `draw_3d_view()`:

1. **`init_ray()`** — computes the camera-space coordinate `camera_x = 2·x/NUM_RAYS − 1 ∈ [−1, 1]` and the ray direction `ray_dir = dir + plane · camera_x`.
2. **`calculate_step_and_side_dist()`** — determines the grid step direction and the initial distance to the next cell boundary.
3. **`perform_dda()`** — steps the ray cell by cell until it hits a wall, then computes the perpendicular wall distance (avoiding fish-eye distortion).
4. **`draw_wall_stripe()`** — projects the wall height (`line_height = WINDOW_HEIGHT / perp_wall_dist`), selects the correct face texture via `select_texture()`, and maps the texture column onto the screen.

The player's direction is derived from the camera angle as `dir = (cos θ, sin θ)` and `plane = (−sin θ · 0.66, cos θ · 0.66)`, where `0.66` sets the field of view.

See [MATEMATICA.md](MATEMATICA.md) for the full math behind the engine.

---

## Project Structure

```
Cub3D/
├── main.c                  # Entry point, game loop, MLX hooks
├── cub3d.h                 # Structures and prototypes
├── raycasting.c            # 3D view rendering
├── raycasting_utils.c      # DDA, ray init, texture sampling
├── draw_map.c / draw_map2.c
├── draw_player.c / draw_player_utils.c
├── movements.c             # Movement / strafing
├── collision.c             # Collision detection
├── hooks_handler.c         # Keyboard & mouse input
├── hooks_handler_utils.c
├── cleanup.c               # Memory cleanup
├── utils.c
├── parsing/                # Scene file parsing & validation
│   ├── parse_file.c
│   ├── parse_textures.c
│   ├── parse_colors.c
│   ├── parse_map.c
│   ├── validate_map.c
│   └── ...
├── maps/                   # Example .cub scenes
├── textures/               # Wall textures (.xpm)
├── libft/                  # Custom C standard library
├── minilibx-linux/         # Graphics library
└── Makefile
```

---

## Configuration

Key constants can be tuned in `cub3d.h`:

| Constant        | Default | Description                       |
| --------------- | ------- | --------------------------------- |
| `WINDOW_WIDTH`  | 1024    | Window width in pixels            |
| `WINDOW_HEIGHT` | 512     | Window height in pixels           |
| `NUM_RAYS`      | 1024    | Rays cast per frame (one/column)  |
| `MOVE_SPEED`    | 1.33    | Movement speed                    |
| `ROT_SPEED`     | 0.075   | Rotation speed                    |
| `MINIMAP_WIDTH` | 320     | Minimap width cap                 |
| `TILE`          | 32      | Tile size in pixels               |

---

## Author

**Vlad-Darius Turlas**
