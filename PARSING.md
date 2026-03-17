# Parsing in Cub3D

## Scop
Partea de parsing construieste structura `t_cub` din fisierul `.cub`:
- cai catre texturi (`NO`, `SO`, `WE`, `EA`)
- culori pentru `F` (floor) si `C` (ceiling)
- harta 2D (`map.grid`)
- pozitia si directia initiala a playerului

## Flux logic
1. `parse_cub_file()` (`parsing/parse_file.c`) deschide fisierul si initializeaza `t_cub` prin `init_cub()`.
2. Fiecare linie este citita cu `read_line()` (`parsing/parse_file_utils.c`).
3. `process_line()` decide ce reprezinta linia:
- textura (`parse_textures`)
- culoare (`parse_color_line`)
- inceput de harta (`is_map_line` + `add_map_line`)
4. La final se valideaza prezenta tuturor elementelor prin `check_all_elements()`.
5. `validate_map()` verifica daca harta este valida (non-goala, un singur spawn, inchisa).

## Validari importante
- Extensie fisier intrare: `.cub`.
- Texturi:
- fiecare ID apare o singura data
- calea exista pe disk
- fisierul are extensia `.xpm`
- Culori:
- format strict `R,G,B`
- exact 3 componente
- fiecare componenta in intervalul `0..255`
- Harta:
- contine exact un caracter de spawn (`N/S/E/W`)
- orice celula traversabila (`0` sau spawn) trebuie sa fie inconjurata in 4 directii, fara iesire in afara hartii sau in spatii goale

## Functii cheie si rolul lor
- `init_cub()` (`parsing/parse_file_utils.c`): seteaza starea initiala a structurii; culorile pornesc cu `-1` ca marker "neparsate".
- `process_line()` (`parsing/parse_file_utils.c`): dispatcher-ul principal pentru liniile din fisier.
- `parse_textures()` (`parsing/parse_textures.c`): parseaza si valideaza liniile de textura, previne duplicatele.
- `parse_color_line()` + `parse_rgb()` (`parsing/parse_colors.c`): parseaza culori `F/C` si converteste in `hex` prin `rgb_to_hex()`.
- `add_map_line()` (`parsing/parse_map.c`): adauga incremental o linie in `map.grid`.
- `normalize_map()` (`parsing/parse_map.c`): aduce toate liniile la aceeasi latime, completand cu spatii.
- `find_player()` (`parsing/parse_map.c`): cauta si valideaza unicitatea spawn-ului.
- `validate_map_closed()` (`parsing/validate_map.c`): verifica inchiderea hartii in jurul tuturor celulelor traversabile.
- `init_player_from_map()` (`parsing/parse_file.c`): transforma spawn-ul din grid in coordonate/pornire pentru motorul de joc (`dir` + `plane`).

## Detalii de implementare utile
- Citirea se face caracter-cu-caracter in `read_line()`; simplu, dar suficient pentru formatul `.cub`.
- Harta este stocata ca `char **`, iar alocarea creste la fiecare linie (`allocate_new_grid` + `process_new_line`).
- Spatiile din harta sunt tratate explicit la validare ca zona invalida pentru celule traversabile.
- Conversia spawn grid -> coordonate world se face in pixeli: `player.x = map_x * TILE + TILE / 2`.
