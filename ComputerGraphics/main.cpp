#include <iostream>
#include "Image.h"
#include "EdgeDetector.h"
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Image* machine = new Image("machine.png");
    EdgeDetector::LaplaceOperator(*machine).isSaved("Laplace.png");
    EdgeDetector::RobertsOperator(*machine).isSaved("Roberts.png");
    EdgeDetector::SobelOperator(*machine).isSaved("Sobel.png");


    return 0;
}
