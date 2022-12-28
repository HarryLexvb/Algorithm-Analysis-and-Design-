/*Author: Harold Alejandro Villanueva Borda
 * Date: 20/06/2022
 * Department: Computer Science
 * Curse: Algorithm Analysis and Design 
 * Institution: San Pablo Catholic University of Arequipa
*/

#include <iostream>

#include "Application.h"

int main()
{
    try {
        Application app;

        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}