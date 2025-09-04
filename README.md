# Wolfstein 3D: Oktoberfest Edition ٩(｡•́‿•̀｡)۶

A reimagined mini-game inspired by *Wolfstein 3D* with an Oktoberfest twist! Developed in **C** using the **MiniLibX** graphical library. 

**Platform:** Linux only  
**Collaborators:** [@Gamadays (Tobi)](https://github.com/Gamadays)

---
# Gameplay Video ˙✧˖°🎬 ⋆｡˚꩜

[![Wolfstein 3D: Oktoberfest Edition](https://img.youtube.com/vi/GLjqHxh7r80/0.jpg)](https://www.youtube.com/watch?v=GLjqHxh7r80)

Click the image to watch the video on YouTube!

## Features (◕‿◕)

- **Pfand (Empty Bottle Collection)**: Gather empty bottles to earn money.
- **Pfandautomat**: Trade collected bottles for a ticket to save your earnings.
- **Toggleable Menu**: Easily switch game options.
- **1st and 3rd Person View**: Experience Oktoberfest from different perspectives.
- **Shops**: Buy pretzels and beer at the Brezel and Beer Shops.
- **Inventory System**: Hold and manage various items.
- **Dynamic Movement**: Smooth mouse and arrow key controls.
- **Mini-map**: Stay oriented in the Oktoberfest maze.
- **Fancy Skybox**: Enjoy moving clouds in the background.

---

## Parsing Rules (*´▽`*)

### Map Rules  
1. **Maze Representation**:  
   - `0`: Empty space  
   - `1`: Wall  
   - `N`, `S`, `E`, `W`: Player's starting position  
   - Spaces between walls are allowed.

2. **Map Integrity**:  
   - Must be closed (surrounded by walls).  
   - Always comes **last** in the file.

### File Format
- **Textures and Colors**:
  - Must precede the map.  
  - Separated by one or more empty lines.  
  - Spaces are allowed between values.

- **Floor and Ceiling**:
  - Can be defined as **RGB values** or **textures**.

---

## Fancy Features °˖✧◝(⁰▿⁰)◜✧˖°
- Custom implementation of **ray-casting** and **object ray-casting**.  
- **Skybox** for realistic, moving clouds.  
- **xMath** library for mathematical calculations.  
- **Memory Management**: Custom destructor to prevent memory leaks.  
- AI-generated textures, modified and redrawn for authenticity.

---

## How to Run (´｡• ω •｡`)

1. Clone the repository:
   ```bash
   git clone https://github.com/fraumarzhuk/cub3d.git
   cd cub3d
   ```

2. Compile the project:
   ```bash
   make
   make bonus
   ```

3. Run the game:
   ```bash
   ./cub3d maps/map_bonus.cub
   ```

---

## Credits 	ヽ(°〇°)ﾉ
Developed  by **[Mari](https://github.com/fraumarzhuk)** and **[@Gamma-42 (Tobi)](https://github.com/Gamma-42)**.
