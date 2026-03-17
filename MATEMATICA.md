# Matematica si Raycasting in Cub3D

## Scop
Partea de matematica converteste harta 2D intr-o imagine 3D pseudo-perspectiva folosind raycasting (DDA), plus miscare, coliziuni si minimap scalat.

## Reprezentari folosite
- Pozitia playerului este in pixeli: `player.x`, `player.y`.
- Directia privirii este vectorul unitar `(dir_x, dir_y)`.
- Planul camerei este vectorul perpendicular `(plane_x, plane_y)`; controleaza FOV-ul.
- Harta pentru coliziune/raycasting este pe celule (tile), de aceea apar conversii frecvente `world / TILE`.

## Fluxul de raycasting (pe fiecare coloana)
Implementat in `draw_3d_view()` (`raycasting.c`) pentru `x = 0 .. NUM_RAYS-1`:

1. `init_ray()` (`raycasting_utils.c`)
- calculeaza `camera_x = 2*x/NUM_RAYS - 1` in intervalul `[-1, 1]`
- construieste directia razei:
`ray_dir = dir + plane * camera_x`
- calculeaza `delta_dist_x` si `delta_dist_y` (costul de traversare intre linii de grid)

2. `calculate_step_and_side_dist()`
- stabileste sensul de mers pe grid (`step_x`, `step_y`)
- calculeaza prima distanta pana la urmatoarea frontiera de celula (`side_dist_x`, `side_dist_y`)

3. `perform_dda()`
- avanseaza raza celula-cu-celula pe axa cu `side_dist` mai mica
- se opreste la perete (`'1'`) sau la iesire din harta
- calculeaza `perp_wall_dist` (distanta perpendiculara fata de camera), esentiala pentru a evita fish-eye

4. `draw_wall_stripe()` (`raycasting.c`)
- inaltime perete proiectata:
`line_height = WINDOW_HEIGHT / perp_wall_dist`
- determina segmentul vertical desenat (`draw_start`, `draw_end`)
- alege textura corecta cu `select_texture()` in functie de latura lovita
- mapeaza coordonata X pe textura (`tex_x`) si itereaza Y (`tex_y`) cu pasul `step`

## Miscare, rotatie, coliziuni
- `movements_up_down()` si `movements_left_right()` (`movements.c`):
- W/S: translatie pe vectorul directie
- A/D: translatie pe vectorul planului camerei (strafing)
- `check_collision()` (`collision.c`): blocheaza intrarea in pereti sau iesirea din harta.
- `handle_mouse_move()` (`hooks_handler.c`):
- actualizeaza `player.angle`
- reconstruieste `dir` si `plane` cu trigonometrie:
`dir = (cos(angle), sin(angle))`
`plane = (-sin(angle) * 0.66, cos(angle) * 0.66)`

### Bug real rezolvat: iesire pe marginea hartii
- Caz: o linie din map poate avea lungime diferita fata de celelalte (de exemplu `...0001` cu un `1` in plus la dreapta).
- In validare/normalizare, liniile mai scurte sunt completate cu `' '` (spatiu).
- Daca in coliziune nu tratezi `' '` ca obstacol, playerul poate "prinde" un pixel la margine si intra in afara hartii.
- Efect: iesire out-of-bounds si posibil `segmentation fault` in update/raycasting.
- Fix aplicat: in `check_collision()`, pe langa `'1'`, si `' '` este tratat ca zid (ne-traversabil).

## Minimap si geometrie 2D
- Scara minimap este calculata din dimensiunea hartii, limitata de `MINIMAP_WIDTH` si `WINDOW_HEIGHT` (`draw_map.c`).
- Jucatorul este desenat ca cerc plin (`draw_circle_line`) si orientare ca segment (`cos/sin`).
- Razele pe minimap folosesc aceeasi distanta `perp_wall_dist` pentru a trasa pana la punctul de impact (`draw_rays_on_minimap`).
- Segmentul 2D este desenat cu Bresenham (`init_bresenham`, `update_line_pos`).

## Functii cheie si ce fac
- `init_ray()` (`raycasting_utils.c`): transforma o coloana de ecran intr-o raza in world space.
- `perform_dda()` (`raycasting_utils.c`): intersectie rapida cu grid-ul pana la obstacol.
- `draw_wall_stripe()` (`raycasting.c`): proiectie 3D + texturare pe coloana curenta.
- `select_texture()` (`raycasting_utils.c`): selecteaza `N/S/E/W` pe baza laturii lovite.
- `get_texture_color()` (`raycasting_utils.c`): citeste culoarea din bufferul texturii la `(tex_x, tex_y)`.
- `movements_up_down()` / `movements_left_right()` (`movements.c`): aplica dinamica de deplasare.
- `check_collision()` (`collision.c`): validare pozitie noua in grid.
- `update_player_vectors()` (`hooks_handler.c`): sincronizeaza unghiul cu vectorii folositi de raycasting.

## Observatie practica
Constanta `0.66` folosita pentru planul camerei defineste FOV-ul efectiv. Daca o cresti, vezi mai mult lateral; daca o scazi, imaginea devine mai "zoom-in".
