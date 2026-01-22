# Cub3D - Documentație Tehnică

## Descriere Generală
Cub3D este o implementare a unui motor de raycasting 3D inspirat de Wolfenstein 3D. Proiectul folosește MiniLibX pentru rendering și citește hărți din fișiere `.cub`.

---

## 1. main.c

### `int update_game(t_game *game)`
**Funcția principală a game loop-ului care actualizează starea jocului.**
- Procesează mișcarea jucătorului bazată pe tastele apăsate (W/A/S/D)
- Verifică coliziunile înainte de a aplica mișcarea
- Șterge ecranul (cu negru)
- Desenează vizualizarea 3D
- Afișează imaginea finală în fereastră
- Se execută în fiecare frame

### `int main(int argc, char **argv)`
**Punctul de intrare al programului.**
- Verifică argumentele (necesită exact un fișier .cub)
- Parsează fișierul de hartă
- Inițializează MiniLibX și creează fereastra
- Încarcă toate texturile
- Inițializează poziția și direcția jucătorului
- Ascunde cursorul mouse-ului și îl centrează
- Setează hook-urile pentru evenimente (tastatură, mouse, închidere)
- Pornește loop-ul principal MLX

---

## 2. hooks_handler.c

### `static void update_player_vectors(t_game *game)`
**Actualizează vectorii de direcție și planul camerei bazat pe unghiul jucătorului.**
- Calculează dir_x și dir_y folosind cos/sin
- Calculează plane_x și plane_y (planul camerei, perpendicular pe direcție)
- Factor de scaling 0.66 pentru câmpul vizual

### `int handle_mouse_move(int x, int y, t_game *game)`
**Gestionează mișcarea mouse-ului pentru rotația camerei.**
- Calculează delta_x (diferența de poziție)
- Rotește camera proporțional cu mișcarea mouse-ului (factor 0.002)
- Re-centrează mouse-ul când ajunge la marginile ferestrei
- Previne jump-uri mari (> 200 pixeli)

### `int handle_key(int keycode, t_game *game)`
**Gestionează apăsarea tastelor.**
- ESC (65307): Închide jocul
- W (119): Activează mișcarea înainte (keys[0])
- S (115): Activează mișcarea înapoi (keys[1])
- A (97): Activează mișcarea la stânga (keys[2])
- D (100): Activează mișcarea la dreapta (keys[3])

### `int handle_key_release(int keycode, t_game *game)`
**Gestionează eliberarea tastelor.**
- Dezactivează flag-ul corespunzător din array-ul keys[]
- Permite mișcare continuă (smooth movement)

### `int close_game(t_game *game)`
**Închide jocul și eliberează toate resursele.**
- Apelează cleanup_game() pentru curățare
- Termină programul cu exit(0)

---

## 3. raycasting.c

### `static void init_ray(t_ray *ray, t_game *game, int x)`
**Inițializează o rază pentru un pixel X dat.**
- Calculează camera_x: poziția pe planul camerei (-1 la 1)
- Calculează direcția razei (dir_x, dir_y)
- Determină celula de hartă inițială (map_x, map_y)
- Calculează delta_dist: distanța necesară pentru a traversa o celulă
- Gestionează diviziune la zero (folosește 1e30 pentru direcții aproape de 0)

### `static void calculate_step_and_side_dist(t_ray *ray, t_game *game)`
**Calculează direcția pas-ului și distanța inițială până la următoarea grilă.**
- Determină step_x și step_y: -1 sau 1 (direcția pe grilă)
- Calculează side_dist_x și side_dist_y: distanța până la următoarea linie de grilă
- Se folosește pentru algoritmul DDA (Digital Differential Analysis)

### `static void perform_dda(t_ray *ray, t_game *game)`
**Execută algoritmul DDA pentru a găsi primul perete lovit.**
- Avansează raza pas cu pas pe grilă
- Alege întotdeauna direcția cu side_dist mai mică
- Marchează side = 0 pentru pereți verticali (X), side = 1 pentru orizontali (Y)
- Se oprește când lovește un perete ('1') sau ieșire din hartă
- Calculează perp_wall_dist: distanța perpendiculară la perete (previne fish-eye effect)

### `static t_texture *select_texture(t_game *game, t_ray *ray)`
**Selectează textura corectă bazată pe direcția din care s-a lovit peretele.**
- Side 0 (verticală): EST dacă step_x > 0, VEST altfel
- Side 1 (orizontală): SUD dacă step_y > 0, NORD altfel

### `static int get_texture_color(t_texture *tex, int tex_x, int tex_y)`
**Extrage culoarea unui pixel din textură.**
- Verifică bounds (returnează magenta 0xFF00FF dacă e out of bounds)
- Calculează adresa în memoria texturii
- Returnează culoarea ca int

### `static void draw_wall_stripe(t_game *game, t_ray *ray, int x)`
**Desenează o linie verticală de perete pentru un pixel X.**
- Calculează wall_x: poziția exactă unde raza lovește peretele (0-1)
- Selectează coordonata X din textură
- Calculează înălțimea liniei bazată pe distanță
- Calculează draw_start și draw_end (cu clipping)
- Desenează ceiling de la top până la draw_start
- Desenează textura de perete cu scaling corect
- Desenează floor de la draw_end până la bottom

### `void draw_3d_view(t_game *game)`
**Funcția principală de raycasting care desenează întreaga vizualizare 3D.**
- Lansează NUM_RAYS (1024) raze, una pentru fiecare coloană de pixeli
- Pentru fiecare rază: inițializează, calculează, execută DDA, desenează
- Rezultatul final este o vedere 3D texturată

---

## 4. draw_map.c

### `static void draw_vertical_line(t_img *img, int x, int y, int len, int color)`
**Desenează o linie verticală.**
- Pornind de la (x, y), desenează len pixeli în jos
- Folosit pentru grid-ul minimapei

### `static void draw_horizontal_line(t_img *img, int x, int y, int len, int color)`
**Desenează o linie orizontală.**
- Pornind de la (x, y), desenează len pixeli la dreapta
- Folosit pentru grid-ul minimapei

### `static void draw_tile(t_img *img, int x, int y, int color)`
**Umple un pătrat TILE x TILE cu o culoare.**
- Folosit pentru a desena pereții pe minimapă

### `void draw_map(t_game *game)`
**Desenează minimapa 2D (momentan comentată în main).**
- Umple background-ul cu gri închis
- Desenează pătrate albe pentru pereți ('1')
- Desenează grid-ul cu linii negre
- Limitată la MINIMAP_WIDTH x WINDOW_HEIGHT

---

## 5. draw_player.c

### `void draw_circle(t_img *img, int cx, int cy, int r, int color)`
**Desenează un cerc plin.**
- Folosește algoritmul simplu: testează fiecare pixel dacă e în raza cercului
- Folosit pentru a marca poziția jucătorului pe minimapă

### `void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)`
**Desenează o linie între două puncte folosind algoritmul Bresenham.**
- Algoritm eficient pentru desenarea liniilor
- Folosit pentru a desena direcția jucătorului pe minimapă

### `void draw_player_2d(t_game *game)`
**Desenează reprezentarea 2D a jucătorului (pentru minimapă).**
- Cerc roșu pentru poziția jucătorului
- Linie galbenă pentru direcția de vizualizare (15 pixeli)

---

## 6. collision.c

### `int check_collision(t_game *game, double x, double y)`
**Verifică dacă o poziție dată (x, y) ar cauza o coliziune.**
- Convertește coordonate din pixeli în celule de hartă
- Verifică dacă e în afara graniței hărții (returnează 1 - coliziune)
- Verifică dacă celula conține un perete '1' (returnează 1 - coliziune)
- Returnează 0 dacă poziția e validă

---

## 7. utils.c

### `void my_mlx_pixel_put(t_img *img, int x, int y, int color)`
**Setează culoarea unui pixel într-o imagine MLX.**
- Calculează offset-ul în buffer-ul de imagine
- Scrie direct culoarea în memorie
- Mult mai rapid decât mlx_pixel_put pentru multe pixeli

---

## 8. cleanup.c

### `void cleanup_game(t_game *game)`
**Eliberează toate resursele alocate.**
- Distruge toate imaginile de textură
- Eliberează structura t_cub (inclusiv harta)
- Distruge imaginea de rendering
- Distruge fereastra
- Distruge display-ul MLX
- Eliberează structura MLX

---

## 9. map.c

**Conține vechea hartă hardcodată (10x10), păstrată pentru referință.**
- Nu mai este folosită în codul actual
- Harta se încarcă acum dinamic din fișiere .cub

---

## 10. parsing/parse_file.c

### `static t_cub *init_cub(void)`
**Inițializează structura t_cub cu valori default.**
- Alocă memorie pentru t_cub
- Setează toate câmpurile la 0/NULL
- Setează floor.r/g/b și ceiling.r/g/b la -1 (indicator de "nedefinit")

### `static int check_all_elements(t_cub *cub)`
**Verifică dacă toate elementele necesare au fost parsate.**
- Verifică prezența tuturor celor 4 texturi (NO, SO, WE, EA)
- Verifică dacă culorile floor și ceiling sunt definite
- Verifică dacă harta există
- Afișează mesaje de eroare specifice pentru ce lipsește

### `static char *read_line(int fd)`
**Citește o linie din fișier caracter cu caracter.**
- Construiește string-ul concatenând caractere
- Se oprește la '\n' sau EOF
- Returnează NULL la EOF sau eroare
- Include '\n' în string dacă este prezent

### `static int process_line(t_cub *cub, char *line, int *map_started)`
**Procesează o linie din fișierul .cub.**
- Ignoră liniile goale
- Odată ce harta începe, toate liniile sunt considerate parte din hartă
- Detectează începutul hărții cu is_map_line()
- Încearcă să parseze texturi sau culori dacă nu e hartă
- Returnează 0 pentru eroare, 1 pentru succes

### `t_cub *parse_cub_file(char *filename)`
**Funcția principală de parsing a fișierului .cub.**
- Verifică extensia .cub
- Deschide fișierul
- Inițializează structura t_cub
- Citește și procesează linie cu linie
- Verifică completitudinea elementelor
- Validează harta
- Returnează NULL la eroare, pointer către t_cub la succes

### `void init_player_from_map(t_game *game)`
**Inițializează poziția și direcția jucătorului bazat pe harta parsată.**
- Setează poziția în centrul tile-ului de start
- Setează unghiul, dir_x, dir_y, plane_x, plane_y bazat pe direcția ('N', 'S', 'E', 'W')
- N: -PI/2 (sus), S: PI/2 (jos), E: 0 (dreapta), W: PI (stânga)
- Plane vector: perpendicular pe direcție, lungime 0.66 (FOV)

---

## 11. parsing/parse_textures.c

### `static int parse_texture_line(char *line, char *id, t_texture *tex)`
**Parsează o linie de textură (NO, SO, WE, EA).**
- Verifică dacă linia începe cu identificatorul corect
- Detectează duplicate (eroare)
- Extrage calea fișierului după identificator
- Elimină whitespace
- Verifică extensia .xpm
- Verifică existența fișierului cu access()
- Stochează calea în structura texture

### `int parse_textures(t_cub *cub, char *line)`
**Încearcă să parseze toate tipurile de texturi.**
- Verifică fiecare tip posibil: NO, SO, WE, EA
- Apelează parse_texture_line pentru tipul potrivit
- Returnează 1 dacă a parsat ceva, 0 altfel

### `static int load_texture(t_game *game, t_texture *tex)`
**Încarcă o textură XPM în memorie.**
- Verifică că path-ul există
- Folosește mlx_xpm_file_to_image() pentru a încărca
- Obține adresa buffer-ului de imagine
- Stochează lățime, înălțime și parametri necesari pentru citirea pixelilor
- Returnează 0 la eroare, 1 la succes

### `int load_all_textures(t_game *game)`
**Încarcă toate cele 4 texturi.**
- Apelează load_texture() pentru fiecare direcție
- Se oprește la prima eroare
- Returnează 0 la eroare, 1 la succes

---

## 12. parsing/parse_colors.c

### `static int parse_rgb_component(char *str, int *value)`
**Parsează o singură componentă RGB (0-255).**
- Sare peste whitespace
- Parsează număr întreg
- Verifică că toate caracterele sunt cifre (sau whitespace la final)
- Validează range-ul 0-255
- Stochează valoarea în pointerul value
- Returnează 0 la eroare, 1 la succes

### `int parse_rgb(char *str, t_color *color)`
**Parsează un string RGB în formatul "R,G,B".**
- Split-uiește după virgulă
- Verifică că sunt exact 3 componente
- Parsează fiecare componentă
- Calculează valoarea hex combinată
- Eliberează memoria temporară
- Returnează 0 la eroare, 1 la succes

### `int parse_color_line(t_cub *cub, char *line)`
**Parsează linii de culoare (F sau C).**
- Detectează F (floor) sau C (ceiling)
- Verifică duplicate
- Extrage string-ul RGB după identificator
- Apelează parse_rgb()
- Returnează 0 la eroare, 1 la succes

---

## 13. parsing/parse_map.c

### `int add_map_line(t_map *map, char *line)`
**Adaugă o linie la hartă (realocă array-ul dinamic).**
- Alocă un array nou cu o intrare în plus
- Copiază pointerii vechi
- Duplică linia nouă
- Elimină '\n' dacă există
- Actualizează height și width (dacă e necesar)
- Returnează 0 la eroare de alocare, 1 la succes

### `void normalize_map(t_map *map)`
**Normalizează toate liniile hărții să aibă aceeași lungime.**
- Pentru fiecare linie mai scurtă decât width
- Alocă string nou de lungimea width
- Copiază conținutul vechi
- Umple restul cu spații
- Necesară pentru a facilita verificarea coliziunilor

### `int find_player(t_map *map)`
**Găsește poziția de start a jucătorului pe hartă.**
- Caută caracterele 'N', 'S', 'E', 'W'
- Stochează poziția și direcția în structura map
- Verifică că există exact o poziție de start (nu 0, nu >1)
- Returnează 0 la eroare, 1 la succes

---

## 14. parsing/validate_map.c

### `static int is_valid_pos(t_map *map, int x, int y)`
**Verifică dacă o poziție este în limitele hărții.**
- Returnează 0 dacă e out of bounds
- Returnează 1 dacă e validă

### `static int check_cell_surrounded(t_map *map, int x, int y)`
**Verifică dacă o celulă este complet înconjurată (nu e la margine).**
- Verifică cele 4 direcții (sus, jos, stânga, dreapta)
- Returnează 0 dacă orice vecin e invalid sau spațiu
- Returnează 1 dacă e complet înconjurat de celule valide
- Crucial pentru a verifica că harta este închisă

### `static int validate_map_closed(t_map *map)`
**Verifică că harta este închisă (nu are găuri în pereți).**
- Pentru fiecare celulă liberă ('0', 'N', 'S', 'E', 'W')
- Verifică că e complet înconjurată
- Previne ca jucătorul să poată ieși din hartă
- Returnează 0 la eroare, 1 la succes

### `int validate_map(t_map *map)`
**Funcția principală de validare a hărții.**
- Verifică că harta nu e goală
- Normalizează harta
- Găsește jucătorul
- Verifică că harta e închisă
- Returnează 0 la eroare, 1 la succes

---

## 15. parsing/parse_utils.c

### `char *ft_strtrim_whitespace(char *str)`
**Elimină whitespace de la început și sfârșit.**
- Avansează start peste whitespace
- Retrage end înapoi peste whitespace
- Alocă și returnează substring-ul trimmed
- Returnează "" pentru string-uri goale

### `int is_empty_line(char *line)`
**Verifică dacă o linie conține doar whitespace.**
- Returnează 1 pentru NULL sau doar whitespace
- Returnează 0 dacă are conținut real

### `int starts_with(char *str, char *prefix)`
**Verifică dacă un string începe cu un prefix.**
- Compară caracter cu caracter
- Returnează 1 la match, 0 altfel

### `int ends_with(char *str, char *suffix)`
**Verifică dacă un string se termină cu un suffix.**
- Compară de la sfârșitul string-ului
- Returnează 1 la match, 0 altfel
- Folosit pentru verificarea extensiilor

### `int rgb_to_hex(int r, int g, int b)`
**Convertește RGB (0-255 fiecare) în hex (0xRRGGBB).**
- Folosește bit shifting: (r << 16) | (g << 8) | b
- Returnează int-ul combinat

### `int is_map_line(char *line)`
**Detectează dacă o linie aparține hărții.**
- Verifică că toate caracterele sunt valide pentru hartă (0, 1, N, S, E, W, spațiu)
- Verifică că linia are cel puțin un caracter de hartă (nu doar spații)
- Returnează 1 pentru linie de hartă, 0 altfel

---

## 16. parsing/parse_error.c

### `int error_msg(char *msg)`
**Afișează un mesaj de eroare și returnează 0.**
- Util pentru funcții care returnează int success/fail
- Permite `return error_msg("Error: ...")` într-o singură linie

### `void *error_null(char *msg)`
**Afișează un mesaj de eroare și returnează NULL.**
- Util pentru funcții care returnează pointeri
- Permite `return error_null("Error: ...")` într-o singură linie

### `void free_split(char **split)`
**Eliberează un array de string-uri.**
- Eliberează fiecare string individual
- Eliberează array-ul în sine
- Safe pentru NULL

### `void free_cub(t_cub *cub)`
**Eliberează complet o structură t_cub.**
- Eliberează toate path-urile de texturi
- Eliberează toate liniile hărții
- Eliberează grid-ul
- Eliberează structura în sine
- Safe pentru NULL

---

## Structuri de Date

### `t_texture`
- **img**: Pointer către imagine MLX
- **addr**: Adresa buffer-ului de pixeli
- **width, height**: Dimensiuni textură
- **bpp**: Bits per pixel
- **line_len**: Lungime linie în bytes
- **endian**: Ordine byte
- **path**: Calea fișierului XPM

### `t_color`
- **r, g, b**: Componente RGB (0-255)
- **hex**: Valoare combinată (0xRRGGBB)

### `t_map`
- **grid**: Array 2D de caractere (harta propriu-zisă)
- **width, height**: Dimensiuni hartă
- **player_x, player_y**: Poziția de start a jucătorului
- **player_dir**: Direcția inițială ('N', 'S', 'E', 'W')

### `t_cub`
- **tex_north/south/west/east**: Cele 4 texturi
- **floor, ceiling**: Culorile podelei și tavanului
- **map**: Structura hărții
- **fd**: File descriptor (folosit în parsing)

### `t_ray`
- **camera_x**: Poziție pe planul camerei (-1 la 1)
- **dir_x, dir_y**: Direcția razei
- **map_x, map_y**: Celula curentă pe hartă
- **side_dist_x, side_dist_y**: Distanță până la următoarea linie de grilă
- **delta_dist_x, delta_dist_y**: Distanță pentru a traversa o celulă
- **step_x, step_y**: Direcția pas-ului (-1 sau 1)
- **hit**: Flag pentru coliziune
- **side**: 0 pentru perete vertical, 1 pentru orizontal
- **perp_wall_dist**: Distanța perpendiculară la perete

### `t_img`
- **img**: Pointer către imagine MLX
- **addr**: Adresa buffer-ului
- **bpp, line_len, endian**: Parametri imagine

### `t_player`
- **x, y**: Poziția în pixeli
- **angle**: Unghiul de rotație în radiani
- **dir_x, dir_y**: Vector direcție (normalizat)
- **plane_x, plane_y**: Planul camerei (perpendicular pe direcție)

### `t_game`
- **mlx**: Pointer către instanța MLX
- **window**: Pointer către fereastră
- **player**: Structura jucătorului
- **map_img**: Imaginea de rendering
- **cub**: Pointer către datele parsate din .cub
- **keys[4]**: Array de flag-uri pentru taste (W, S, A, D)
- **mouse_x, mouse_y**: Poziția mouse-ului

---

## Constante

- **TILE**: 32 - Dimensiunea unei celule de hartă în pixeli
- **WINDOW_WIDTH**: 1024 - Lățimea ferestrei
- **WINDOW_HEIGHT**: 512 - Înălțimea ferestrei
- **MOVE_SPEED**: 1.33 - Viteza de mișcare a jucătorului
- **ROT_SPEED**: 0.075 - Viteza de rotație (nefolosit în versiunea actuală)
- **PI**: 3.14159 - Constanta matematică
- **NUM_RAYS**: 1024 - Numărul de raze (= WINDOW_WIDTH pentru 1 rază/coloană)
- **MINIMAP_WIDTH**: 320 - Lățimea minimapei

---

## Flow-ul Programului

1. **Inițializare**:
   - Parse fișier .cub → t_cub
   - Validare hartă
   - Init MLX, fereastră, imagine
   - Load texturi
   - Init player

2. **Game Loop** (update_game):
   - Procesare input (taste)
   - Update poziție player (cu collision check)
   - Clear screen
   - Raycasting (draw_3d_view)
   - Display

3. **Raycasting per frame**:
   - Pentru fiecare coloană (0 la 1023):
     - Init rază
     - Calculate step
     - DDA (găsește perete)
     - Select textură
     - Draw coloană verticală

4. **Cleanup**:
   - Destroy imagini
   - Free harta
   - Destroy fereastră
   - Free MLX

---

## Algoritmi Cheie

### DDA (Digital Differential Analysis)
- Traversează grila hărții pas cu pas
- Alege întotdeauna direcția cu distanță mai mică
- Eficient pentru raycasting pe grid

### Bresenham Line Drawing
- Algoritm pentru desenarea liniilor
- Folosit pentru minimapă și debugging

### Raycasting
- Lansează raze din poziția jucătorului
- Fiecare rază corespunde unei coloane de pixeli
- Calculează distanța la perete pentru a determina înălțimea
- Aplică texturi cu perspective-correct mapping

### Texture Mapping
- Calculează coordonata X din textură (wall_x)
- Scalează textură vertical (step, tex_pos)
- Evită fish-eye folosind perpendicular wall distance

---

## Note de Performanță

- **my_mlx_pixel_put()** scrie direct în buffer → mult mai rapid decât mlx_pixel_put()
- **Raycasting** este O(N) per frame, unde N = NUM_RAYS
- **DDA** este O(M) per rază, unde M = dimensiunea hărții
- **Continuous key detection** (keys[] array) permite mișcare smooth
- **Mouse re-centering** previne lock-ul la margini

---

## Posibile Îmbunătățiri

1. **Sprites** - Adăugare obiecte 2D în 3D
2. **Floor/Ceiling texturing** - Texturi în loc de culori solide
3. **Lighting** - Shading bazat pe distanță
4. **Minimap toggle** - Activare/dezactivare cu tastă
5. **Multiple level support** - Încărcare hărți multiple
6. **Animations** - Texturi animate
7. **Sound** - Efecte sonore
8. **Optimizări** - Multi-threading, SIMD

---

## Erori Comune și Debugging

### "Segmentation fault"
- Verificați bounds în get_texture_color()
- Verificați că harta e normalizată
- Verificați că texturile sunt încărcate

### "Fish-eye effect"
- Folosiți perp_wall_dist, nu distanța reală
- Verificați calculele de camera_x

### "Texturi distorsionate"
- Verificați calculul tex_x (trebuie < width)
- Verificați step și tex_pos
- Verificați că tex_y e bounded cu (& height-1)

### "Map leaks"
- Rulați validate_map_closed()
- Verificați că toate celulele libere sunt înconjurate

### "Memory leaks"
- Folosiți valgrind
- Verificați că toate malloc-urile au free corespondent
- Nu uitați de cleanup_game() la exit

---

*Documentație generată pentru proiectul Cub3D - O implementare educațională de raycasting engine*
