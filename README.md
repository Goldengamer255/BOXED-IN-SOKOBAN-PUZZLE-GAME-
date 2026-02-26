# Boxed In — Sokoban Puzzle Game 📦

A fully playable terminal-based Sokoban-style puzzle game built in C, featuring a 10x10 grid engine with real-time collision handling, multi-box pushing, target tracking, and full undo support via stack-based state management.

---

## 🚀 Features

- **10x10 2D grid engine** supporting 100+ warehouse configurations
- **WASD movement** with real-time collision and boundary detection
- **Multi-box pushing** with wall and double-box block detection
- **Target tracking** — boxes and player change state when on target squares
- **Full undo system** (`z`) — reverses any move including box pushes
- **Symbolic display** — visual representation of all game states
- **1,000+ sequential moves** supported with stable memory management

---

## 🛠️ Tech Stack

- C
- 2D Array Grid Engine
- Stack-Based State Management

---

## 📂 Project Structure

```
├── sokoban.c       # All game logic — main entry point, movement, undo, rendering
└── README.md
```

---

## 🏃 How to Run

1. Clone the repository:
```bash
git clone https://github.com/YOURUSERNAME/sokoban-puzzle-game.git
```

2. Compile:
```bash
gcc sokoban.c -o sokoban
```

3. Run:
```bash
./sokoban
```

---

## 🗺️ How to Set Up a Level

Levels are defined using a **layout string** passed to `InitialiseRoom()`. Each character maps to a tile type on the 10x10 grid (100 characters total).

### Tile Key

| Character | Tile |
|---|---|
| `0` | Empty Space |
| `1` | Wall `#` |
| `2` | Target `*` |
| `3` | Box `O` |
| `4` | Box on Target `@` |
| `5` | Player `X` |
| `6` | Player on Target `X` |

### Example Layout

```c
char layout[200] = "1111111111"
                   "1000000001"
                   "1002000001"
                   "1002005001"
                   "1002000001"
                   "1002000001"
                   "1002222201"
                   "1003000001"
                   "1000000001"
                   "1111111111";
```

> **Tip:** The layout string must be exactly 100 characters for a 10x10 grid. Any missing characters default to walls.

### Initialise the Room

```c
int room[ROWS][COLS];
char layout[200] = "1111111111100000000110020000011002005001100200000110020000011002222201100300000110000000011111111111";
char moves[100] = {0};

InitialiseRoom(room, layout);
```

---

## 🎮 How to Play

Moves are made by calling `MakeMove()` with the room, a direction character, and the move history string.

### Movement Commands

| Key | Direction |
|---|---|
| `w` | Move Up |
| `s` | Move Down |
| `a` | Move Left |
| `d` | Move Right |
| `z` | Undo Last Move |

### Example

```c
MakeMove(room, 'w', moves);   // Move up
MakeMove(room, 'd', moves);   // Move right
MakeMove(room, 's', moves);   // Move down
MakeMove(room, 'z', moves);   // Undo last move
PrintRoom(room);               // Render current state
printf("Moves: %s", moves);   // Print move history
```

### Movement Rules
- Player **cannot move into walls**
- Player **can push a single box** if the space behind it is empty or a target
- Player **cannot push two boxes** in a row
- Player **cannot push a box into a wall**
- Undo (`z`) fully reverses the last move including any box that was pushed

---

## 📊 Highlights

| Feature | Detail |
|---|---|
| Grid Size | 10x10 |
| Supported Configurations | 100+ |
| Unique Move Interactions | 50+ |
| Max Sequential Moves | 1,000+ |
| Undo System | Stack-based, full state reversal |

---

## 🎓 What I Learned

- Building a 2D grid-based game engine from scratch in C
- Implementing stack-based undo logic with encoded move history
- Handling complex collision detection across 50+ unique interaction cases
- Managing stable 2D array memory across 1,000+ sequential operations

---

## 📬 Contact

**Tanush Panuganti**
- GitHub: [Goldengamer255](https://github.com/Goldengamer255)
- LinkedIn: [tanush-panuganti](https://linkedin.com/in/tanush-panuganti)
- Email: tanush.panu@gmail.com
