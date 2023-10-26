#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

int height = 3;
int animation = 0;

void print_tower(std::vector<int> rods[])
{
  // Print rods from top to bottom
  for (int i = height-1; i >= 0; i--) {
    if (i < rods[0].size())
      std::cout << " " << rods[0][i];
    else
      std::cout << " |";

    if (i < rods[1].size())
      std::cout << " " << rods[1][i];
    else
      std::cout << " |";

    if (i < rods[2].size())
      std::cout << " " << rods[2][i];
    else
      std::cout << " |";
    std::cout << "\n";
  }
  std::cout << "#######"
            << std::endl
            << std::endl;
}

void move_disc(int from, int to, std::vector<int> rods[])
{
  if (animation > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(animation));

    // Clear screen
    std::cout << "\033[" << height + 2 << "F";
    std::cout << "\033[0J";
  }

  std::cout << "Move disc of size " << rods[from].back()
            << " from rod " << from + 1 << " to rod " << to + 1 << "."
            << std::endl;

  rods[to].push_back(rods[from].back());
  rods[from].pop_back();

  print_tower(rods);
}

int move_stack(int size, int from, int to, int via, std::vector<int> rods[])
{
  int moves = 0;
  if (size > 0) {
    // Move discs above to the via rod
    moves += move_stack(size - 1, from, via, to, rods);

    // Move disc from the from rod to the to rod
    move_disc(from, to, rods);
    moves++;

    // Move discs from the via rod to the to rod via the from rod
    moves += move_stack(size - 1, via, to, from, rods);
  }

  return moves;
}

int main(int argc, char *argv[])
{
  std::vector<int> rods[3];

  // Stack size
  if (argc > 1)
    height = std::strtol(argv[1], nullptr, 10);
  for (int i = height; i > 0; i--)
    rods[0].push_back(i);

  // Animation time
  if (argc > 2)
    animation = std::strtol(argv[2], nullptr, 10);

  std::cout << "Towers of Hanoi" << std::endl;
  print_tower(rods);

  int moves = move_stack(height, 0, 2, 1, rods);

  // Clear screen
  std::cout << "\033[" << height + 2 << "F";
  std::cout << "\033[0J";

  print_tower(rods);

  std::cout << "Moved stack of " << height << " discs in " << moves << " moves."
            << std::endl;
  return 0;
}
