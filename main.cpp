#include <iostream>

#include <iostream>
#include "Solver.h"

int main() {
    Solver solver;
    bool result = solver.findAnswer();

    std::cout << (result ? "Yes\n" : "No\n");
    return 0;
}
