

---

# STATUS ACTUAL AL PROIECTULUI

## ✅ Ce Este Implementat:

### 1. Structură de Bază Completă
- Headers, Makefile cu libft
- Structuri: t_game, t_player, t_img

### 2. Sistem 2D Funcțional  
- Hartă 10×10 hardcodată
- Minimap cu grid, player vizibil

### 3. Mișcare și Control
- W/S înainte/înapoi, A/D rotire
- Detecție coliziuni, ESC închide

### 4. Raycasting de Bază
- 704 raze, FOV 60°, fish-eye correction
- Cer + pereți + podea
- Ecran împărțit: 320px minimap + 704px 3D

### 5. Buffering Corect
- Tot în map_img, performance bun

---

## 🎯 URMĂTORII PAȘI:

### PRIORITATE ÎNALTĂ:

#### 1. Parser .cub (OBLIGATORIU)
Citește fișiere .cub cu texturi, culori și hartă.
Fișiere: parse_file.c, validate_map.c

#### 2. Texturi pe Pereți (OBLIGATORIU)
Încarcă .xpm și desenează pe pereți.

### PRIORITATE MEDIE:

#### 4. Mișcare Strafing
Q/E pentru lateral

### PRIORITATE SCĂZUTĂ:

#### 5. Shading
#### 6. Culori diferite N/S/E/W  
#### 7. Bordere negre
#### 8. Sprite-uri
#### 9. Minimapă îmbunătățită

### BONUS:

Mouse look, porți, animații, skybox, sunet

---

## 🎯 PRIORITATEA #1: Parser pentru .cub
