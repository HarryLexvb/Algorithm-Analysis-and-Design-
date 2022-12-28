// HORSE
#include <iostream>
#include "nqueens/nqueens_9.h"

int
main(int argc, char *argv[])
{
    int n = 0;
    int x = 0;
    int y = 0;

    if (argc == 4) {
        for (char *i = argv[1]; *i != '\0'; i++) {
             if (*i > '9' || *i < '0')
                return -1;
            n = n * 10 + *i - '0';
        }

        for (char *i = argv[2]; *i != '\0'; i++) {
             if (*i > '9' || *i < '0')
                return -1;
            x = x * 10 + *i - '0';
        }

        for (char *i = argv[3]; *i != '\0'; i++) {
             if (*i > '9' || *i < '0')
                return -1;
            y = y * 10 + *i - '0';
        }
    } else if (argc != 2)
        return -1;

    std::cout << nqueens_9(n, x, y) << std::endl;
}
