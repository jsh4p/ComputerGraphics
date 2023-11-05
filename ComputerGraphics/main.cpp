#include <iostream>
#include "Image.h"
#include "EdgeDetector.h"
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Image* machine = new Image("images/cat.png");
    EdgeDetector::LaplaceOperator(*machine).isSaved("images/Laplace.png");
    EdgeDetector::RobertsOperator(*machine).isSaved("images/Roberts.png");
    EdgeDetector::SobelOperator(*machine).isSaved("images/Sobel.png");


    return 0;
}
