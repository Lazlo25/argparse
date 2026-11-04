#include <argparse/argparse.hpp>
#include <iostream>
#include <stdexcept>

int main() {
  argparse::ArgumentParser tiny_brain("parser-amnesia");
  tiny_brain.add_argument("--number").default_value(3).scan<'i', int>();
  tiny_brain.add_argument("--verbose").flag();

  tiny_brain.parse_args({"parser-amnesia", "--number", "7", "--verbose"});
  std::cout << "Round one, soup delivered: number=" << tiny_brain.get<int>("--number")
            << ", verbose=" << tiny_brain.get<bool>("--verbose") << '\n';

#ifdef USE_RESET
  tiny_brain.reset();
  std::cout << "Memory eviction complete.\n";
#else
  std::cout << "Original version: reset() is not available.\n";
#endif

  try {
    tiny_brain.parse_args({"parser-amnesia", "--number", "9"});
    std::cout << "Round two, no haunted leftovers: number=" << tiny_brain.get<int>("--number")
              << ", verbose=" << tiny_brain.get<bool>("--verbose") << '\n';
#ifdef USE_RESET
    tiny_brain.reset();
    tiny_brain.parse_args({"parser-amnesia"});
    std::cout << "Factory brain restored: number=" << tiny_brain.get<int>("--number")
              << ", verbose=" << tiny_brain.get<bool>("--verbose") << '\n';
#endif
  } catch (const std::runtime_error &error) {
    std::cout << "Second parse failed: " << error.what() << '\n';
    return 1;
  }
}
