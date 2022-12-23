#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

// Character class
typedef struct {
  int x;
  int y;
  char symbol;
} Character;

// Tile node
typedef struct TileNode {
  int x;
  int y;
  char type;
  struct TileNode* next;
} TileNode;

// Linked list to store map data
TileNode* map = NULL;

// Adds a new tile to the map
void addTile(int x, int y, char type) {
  TileNode* newTile = malloc(sizeof(TileNode));
  newTile->x = x;
  newTile->y = y;
  newTile->type = type;
  newTile->next = map;
  map = newTile;
}

// Returns the tile at the given position, or NULL if it doesn't exist
TileNode* getTile(int x, int y) {
  TileNode* current = map;
  while (current) {
    if (current->x == x && current->y == y) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// Prototypes
void moveCharacter(Character* character, int dx, int dy);
void renderMap(Character* character);
char generateTile(int x, int y);

int main(int argc, char* argv[]) {
  // Create player character
  Character player = {
    .x = 1,
    .y = 1,
    .symbol = '@'
  };

  // Initialize the ncurses library
  initscr();

  // Enable non-blocking input
  // nodelay(stdscr, TRUE);

  // Game loop
  while (1) {
    // Render map
    renderMap(&player);

    printf("Player position: (%d, %d)\n", player.x, player.y);

    // Get player input
    printf("Enter move (w/a/s/d): ");
    // char input;
    // scanf(" %c", &input);

    char input = getch();

    // Update player position based on input
    switch (input) {
      case 'w':
        moveCharacter(&player, 0, -1);
        break;
      case 'a':
        moveCharacter(&player, -1, 0);
        break;
      case 's':
        moveCharacter(&player, 0, 1);
        break;
      case 'd':
        moveCharacter(&player, 1, 0);
        break;
    }
  }

  // Clean up the ncursed library
  endwin();
  return 0;
}

// Moves the character by the given amount
void moveCharacter(Character* character, int dx, int dy) {
  // Calculate the new position of the character
  int newX = character->x + dx;
  int newY = character->y + dy;

  // Get the tile at the new position
  TileNode* tile = getTile(newX, newY);

  // Check if the tile is a wall
  if (tile && tile->type == '#') {
    // Don't update the character's position
    return;
  }

  // Update the character's position
  character->x = newX;
  character->y = newY;
}


//// random num tileset
char generateTile(int x, int y) {
  float r = (float)rand() / RAND_MAX;
  if (r < 0.2) {
    return '#';
  } else {
    return ' ';
  }
}

void renderMap(Character* character) {
  int x = character->x;
  int y = character->y;

  // Clear the screen
  clear();

  // Center the map on the character's position
  int startX = x - MAP_WIDTH / 2;
  int startY = y - MAP_HEIGHT / 2;

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (x == MAP_WIDTH / 2 && y == MAP_HEIGHT / 2) {
        // Print the character symbol at the center of the map
        addch(character->symbol);
      } else {
        // Get the tile at this position
        TileNode* tile = getTile(startX + x, startY + y);

        // Generate a new tile if it doesn't exist
        if (!tile) {
            addTile(startX + x, startY + y, generateTile(startX + x, startY + y));
            tile = getTile(startX + x, startY + y);
        }

        // Print the tile symbol
        addch(tile->type);
      }
    }
    // Move to the next line after printing a row of tiles
    addch('\n');
  }

  // Refresh the screen to display the changes
  refresh();
}

