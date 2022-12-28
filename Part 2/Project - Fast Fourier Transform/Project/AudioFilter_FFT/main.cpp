/*Author: Harold Alejandro Villanueva Borda
 * Date: 20/06/2022
 * Department: Computer Science
 * Curse: Algorithm Analysis and Design
 * Institution: San Pablo Catholic University of Arequipa
*/

#include "FFT.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900, 32), "ORIGINAL");

    RenderWindow window2(VideoMode(900, 900, 32), "FILTRADO");

    string path;
    int bufferSize;
    int numero;
    bool origen = false;

    cout << "\n\t\t\tFAST FOURIER TRANSFORM\n" <<
         "\t\t\t======================\n\n\n" <<

         "Elija un filtro para usar de la lista con 50 taps\n\n" <<
         "0:Filtro de Low pass con limite superior @ 0.5khz\n" <<
         "1:Filtro de High pass con limite inferior @ 5khz\n" <<
         "2:Filtro de Band pass con limites entre 1khz y 4khz\n";
    cin >> numero;

    ClaseFourier fft(R"(C:\Users\win 10\Documents\CLION\AudioFilter_FFT\Wavs\madoka.ogg)", 16384, numero);

    Event event; //para capturar pulsaciones de teclas, pulsaciones de ratón

    while (window.isOpen() && window2.isOpen())
    {
        while (window.pollEvent(event) || window2.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            //PAUSE
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    fft.ppSound();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    fft.switchSource(origen);
                    origen = !origen;
                }
            }
        }

        fft.update();

        window.clear();
        window2.clear();


        fft.draw(window);
        fft.drawF(window2);

        window.display();
        window2.display();
    }

    return 0;
}
