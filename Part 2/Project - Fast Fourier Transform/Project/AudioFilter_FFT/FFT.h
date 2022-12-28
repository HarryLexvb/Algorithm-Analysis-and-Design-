//
// Created by HarryLex on 20/06/2022.
//

#ifndef AUDIOFILTER_FFT_FFT_H
#define AUDIOFILTER_FFT_FFT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "filt.h"

#include <iostream>
#include <complex>
#include <valarray>

#include <fstream>


using namespace std;
using namespace sf;

const double PI = 3.141592653589793238460;
typedef complex<double> Complex;	//almacen de numeros complejos (real, imaginario)
typedef valarray<Complex> CArray; 	//se utiliza para realizar operaciones matemáticas en cada elemento de la matriz mas facil

class ClaseFourier
{
public:
    ClaseFourier(string const& _path, int const& _bufferSize, int fc);
    ~ClaseFourier()
    {
        delete samples;
        delete filterSamples;
        delete lfSamples;
        for (int i = 0; i < generalFilter.size(); i++)
        {
            delete generalFilter.at(i);
        }
    }
    void hammingWindow();		//función de ventana para centrarse en una muestra de datos de toda la señal
    void fft(CArray& x, CArray& fx);		//realizar faster fourier transform en datos de muestra
    void update();				//para ejecutar continuamente el fft en los datos de sonido y mostrarlos en la pantalla

    void bars(float const& max);	//para dibujar la señal en el dominio de la frecuencia
    void lines(float const& max);  //para dibujar la señal en el dominio del tiempo

    void draw(RenderWindow& window);	//dibujar en la pantalla tanto frecuencia y representaciones temporales
    void drawF(RenderWindow& window);

    int FiltroEscogido;
    void switchSource(bool s);
    void ppSound();		//Pausa-play

    void updateFilterSound();

    bool PrecalculoDeFiltros();
    bool outWAV(string wavName);
    bool outWAV(string wavName, Int16*& fsamples);

    Int16 lpfdataSample(double& s);
    Int16 hpfdataSample(double& s);
    Int16 bpfdataSample(double& s);

private:
    string path;
    SoundBuffer buffer;
    SoundBuffer fbuffer;

    Sound sound;
    Sound fsound;

    vector<Complex> sample;
    vector<Complex> fsample; //muestra de musica ya filtrada para fft

    vector<float> window;

    CArray bin;
    CArray fbin; //bin filtrado

    VertexArray VA1;
    VertexArray VA2;
    VertexArray VA3;

    VertexArray fSignalDeTiempo; //va1 señal de tiempo ya filtrado //array de vertices en la consola para dibujar
    VertexArray fBarras; //va2- filter barras ya filtrado
    VertexArray fCascada; //va3 - efecto cascada frequency ya filtrado

    vector<Vertex> cascade;
    vector<Vertex> vCascadaFiltrada;

    int sampleRate;//frecuencias de las muestras
    int sampleCount;//numero de muestras
    int bufferSize;
    int mark;


    Int16* samples;			//puntero a los datos de la musica
    Int16* filterSamples;
    Int16* lfSamples;
    SoundBuffer fBuffer;
    vector<Filter*> generalFilter;
};

bool ClaseFourier::outWAV(string wavName)
{
    OutputSoundFile file;


    if (!file.openFromFile(wavName, 44100, 2)) return false;

    file.write(buffer.getSamples(), buffer.getSampleCount());
    return true;
}

bool ClaseFourier::outWAV(string wavName, Int16*& fsamples)
{
    OutputSoundFile file;


    if (!file.openFromFile(wavName, 44100, 2)) return false;

    file.write(fsamples, buffer.getSampleCount());

    return true;
}


ClaseFourier::ClaseFourier(string const& _path, int const& _bufferSize, int fc)
{
    FiltroEscogido = fc;
    PrecalculoDeFiltros();

    path = _path; //lugar donde esta la musica
    if (!buffer.loadFromFile(path)) //verifica si se puede leer la musica
    {
        cout << "No se puede cargar la Musica" << endl;
    }
    else
    {
        cout << "> archivo WAV/OGG cargado" << endl;
    }

    sound.setBuffer(buffer); //apuntamos al búfer que declaramos anteriormente para leer los datos del sonido


    sound.setVolume(0.0f);
    updateFilterSound();	//crear un búfer del sonido con la señal filtrada

    sound.play();
    fsound.play();			//toca la musica


    /*Listas para Graficar*/

    //dominio del tiempo
    VA1.setPrimitiveType(LineStrip); 	//Lista de líneas conectadas, un punto usa el punto anterior para formar una línea
    fSignalDeTiempo.setPrimitiveType(LineStrip);

    //frequency domain
    VA2.setPrimitiveType(Lines); 		// Lista individual de lineas
    fBarras.setPrimitiveType(LineStrip);

    //cascade background
    VA3.setPrimitiveType(LineStrip); 	//lista de lineas conectadas
    fCascada.setPrimitiveType(LineStrip);

    sampleRate = buffer.getSampleRate() * buffer.getChannelCount();
    sampleCount = buffer.getSampleCount();


    cout << "______________Comandos de teclado______________" << endl;
    cout << "-----------------------------------------------\n\n" << endl;
    cout << "C:     Alternar de audio o a filtrado o a original" << endl;
    cout << "Space:			play/pause" << endl;

    if (_bufferSize < sampleCount)
    {
        bufferSize = _bufferSize; //si el búfer elegido se ajusta a las muestras, configúrelo; de lo contrario, configúrelo en samplecount
    }
    else
    {
        bufferSize = sampleCount;
    }

    mark = 0; //estamos en tiempo 0: t=0
    float push = 0.0;	//valor temporal para almacenar el valor del la ventana creada

    for (int i(0); i < bufferSize; i++) 	//configurar el búfer de la ventana de hamming
    {
        push = 0.54 - 0.46 * cos(2 * PI * i / (float)bufferSize);
        window.push_back(push);
    }


    //Cambiar el tamaño de la muestra vectorial y vertexarray VA1 al tamaño del tamaño del búfer

    sample.resize(bufferSize);
    VA1.resize(bufferSize);

    fsample.resize(bufferSize);
    fSignalDeTiempo.resize(bufferSize);
}

void ClaseFourier::hammingWindow()
{
    mark = sound.getPlayingOffset().asSeconds() * sampleRate; //calculamos en que muestra de la musica estamos
    if (mark + bufferSize < sampleCount)				//si aun tenemos espacio para analizar
    {
        for (int i(mark); i < mark + bufferSize; i++) //iniciar el window en mark y subimos al tamaño del búfer dado
        {
            sample[i - mark] = Complex(buffer.getSamples()[i] * window[i - mark], 0);

            fsample[i - mark] = Complex(fbuffer.getSamples()[i] * window[i - mark], 0);

            //for drawing the time domain signal
            VA1[i - mark] =
                    Vertex(Vector2f(40, 250) + Vector2f((i - mark) / (float)bufferSize * 750, sample[i - mark].real() * 0.007),
                           Color(0, 255, 0, 50));
            fSignalDeTiempo[i - mark] =
                    Vertex(Vector2f(40, 250) + Vector2f((i - mark) / (float)bufferSize * 750, fsample[i - mark].real() * 0.007),
                           Color::Red);
        }
    }
}

/*
* FAST FOURIER TRANSFORM
* ----------------------
* calcula la DISCRETE FOURIER TRANSFORM en O(nlogn) aplicando divide y vencerás
*/
void ClaseFourier::fft(CArray& x, CArray& fx)
{
    const int N = x.size();
    if (N <= 1) return; //regresa al elemento anterior de la pila

    //Pares
    CArray Pares = x[slice(0, N / 2, 2)]; //cortamos (offset, número de elementos en el nuevo corte, pasos entre elementos de array)
    CArray fPares = fx[slice(0, N / 2, 2)];

    //Impares
    CArray  Impares = x[slice(1, N / 2, 2)];
    CArray fImpares = fx[slice(1, N / 2, 2)];

    fft(Pares, fPares);
    fft(Impares, fImpares);


    for (int k = 0; k < N / 2; k++)
    {
        Complex t = polar(1.0, -2 * PI * k / N) * Impares[k];
        //cout << t;;
        Complex ft = polar(1.0, -2 * PI * k / N) * fImpares[k];
        //cout << "\t" << ft << endl;

        x[k] = Pares[k] + t;
        fx[k] = fPares[k] + ft;

        x[k + N / 2] = Pares[k] - t;
        fx[k + N / 2] = fPares[k]; -ft;
    }
}

void ClaseFourier::update()
{
    hammingWindow();

    VA2.clear();
    fBarras.clear();
    VA3.clear();
    fCascada.clear();


    //transformar el tiempo (muestra de musica) en el dominio de la frecuencia
    //bin de inicio y bin filtrado ( valores de datos de muestra, tamaño de búfer )
    bin = CArray(sample.data(), bufferSize);
    fbin = CArray(fsample.data(), bufferSize);

    fft(bin, fbin);

    float max = 100000000;
    lines(max);
    bars(max);
}

void ClaseFourier::bars(float const& max)
{
    VA2.setPrimitiveType(Lines);
    fBarras.setPrimitiveType(Lines);

    Vector2f position(0, 800);
    for (float i(3); i < min(bufferSize / 2.f, 20000.f); i *= 1.01)
    {
        Vector2f samplePosition(log(i) / log(min(bufferSize / 2.f, 20000.f)), abs(bin[(int)i]));
        Vector2f fPos(log(i) / log(min(bufferSize / 2.f, 20000.f)), abs(fbin[(int)i]));

        VA2.append(Vertex(position + Vector2f(samplePosition.x * 800, -samplePosition.y / max * 700), Color::White));
        fBarras.append(Vertex(position + Vector2f(fPos.x * 800, -fPos.y / max * 700), Color::White));

        //		VA2.append(Vertex(position+Vector2f(samplePosition.x*800,-samplePosition.y/max*500),Color::Green)) ; //peak of bars

        VA2.append(Vertex(position + Vector2f(samplePosition.x * 800, 0), Color::White));
        fBarras.append(Vertex(position + Vector2f(fPos.x * 800, 0), Color::White));
        //		VA2.append(Vertex(position+Vector2f(samplePosition.x*800,0),Color::Green)) ; //body of bars

        VA2.append(Vertex(position + Vector2f(samplePosition.x * 800, 0), Color(255, 255, 255, 100))); //color(r,g,b,alpha);
        fBarras.append(Vertex(position + Vector2f(fPos.x * 800, 0), Color(255, 255, 255, 100))); //color(r,g,b,alpha);

//		VA2.append(Vertex(position+Vector2f(samplePosition.x*800,0),Color::Green)) ; //body of bar reflections

//		VA2.append(Vertex(position+Vector2f(samplePosition.x*800,samplePosition.y/max*500/2.f),Color(255,255,255,0))) ;
        VA2.append(Vertex(position + Vector2f(samplePosition.x * 800, samplePosition.y / max * 500 / 2.f), Color::White)); //peak of bar reflections
        fBarras.append(Vertex(position + Vector2f(fPos.x * 800, fPos.y / max * 500 / 2.f), Color::White)); //peak of bar reflections
    }
}
void ClaseFourier::lines(float const& max)
{
    VA3.setPrimitiveType(LineStrip);
    fCascada.setPrimitiveType(LineStrip);

    Vector2f position(0, 800);
    Vector2f samplePosition;
    Vector2f fpos;
    float colorDecay = 1;

    for (float i(std::max((double)0, cascade.size() - 3e5)); i < cascade.size(); i++)
    {
        cascade[i].position -= Vector2f(3, 3);// graficar(espacios entre lineas de forma horizontal, espacios entre lineas de forma vertical)
        vCascadaFiltrada[i].position -= Vector2f(-3, 3);

        if (cascade[i].color.a != 0)
        {
            cascade[i].color = Color(0, 255, 255, 20);
            vCascadaFiltrada[i].color = Color(0, 255, 255, 20);
        }
    }
    samplePosition = Vector2f(log(3) / log(min(bufferSize / 2.f, 20000.f)), abs(bin[(int)3]));
    fpos = Vector2f(log(3) / log(min(bufferSize / 2.f, 20000.f)), abs(fbin[(int)3]));

    cascade.push_back(Vertex(position + Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500), Color::Transparent));
    vCascadaFiltrada.push_back(Vertex(position + Vector2f(fpos.x * 800, -fpos.y / max * 500), Color::Transparent));

    for (float i(3); i < bufferSize / 2.f; i *= 1.02)
    {
        samplePosition = Vector2f(log(i) / log(min(bufferSize / 2.f, 20000.f)), abs(bin[(int)i]));
        fpos = Vector2f(log(i) / log(min(bufferSize / 2.f, 20000.f)), abs(fbin[(int)i]));

        cascade.push_back(Vertex(position + Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500), Color(255, 255, 255, 20)));
        vCascadaFiltrada.push_back(Vertex(position + Vector2f(fpos.x * 800, -fpos.y / max * 500), Color(255, 255, 255, 20)));
    }
    cascade.push_back(Vertex(position + Vector2f(samplePosition.x * 800, -samplePosition.y / max * 500), Color::Transparent));
    vCascadaFiltrada.push_back(Vertex(position + Vector2f(fpos.x * 800, -fpos.y / max * 500), Color::Transparent));

    VA3.clear();
    fCascada.clear();

    for (int i(std::max((double)0, cascade.size() - 3e5))
            ; i < cascade.size(); i++)
    {
        VA3.append(cascade[i]);
        fCascada.append(vCascadaFiltrada[i]);
    }
}

void ClaseFourier::draw(RenderWindow& window)
{
    window.draw(VA1); //dominio de tiempo
    window.draw(VA3); //cascada
    window.draw(VA2); //dominio frequencia
}
void ClaseFourier::drawF(RenderWindow& window)
{
    window.draw(fSignalDeTiempo);
    window.draw(fCascada);
    window.draw(fBarras);
}
//pauses or plays sound when spacebar is hit
void ClaseFourier::ppSound()
{
    if (sound.getStatus() == Sound::Status::Paused)
    {
        sound.play();
        fsound.play();
    }
    else
    {
        sound.pause();
        fsound.pause();
    }
}


bool ClaseFourier::PrecalculoDeFiltros()
{
    generalFilter.push_back(new Filter(LPF, 50, 44.1, 0.5));
    generalFilter.push_back(new Filter(HPF, 50, 44.1, 5.0));
    generalFilter.push_back(new Filter(BPF, 50, 44.1, 1.0, 4.0));

    for (int i = 0; i < generalFilter.size(); i++)
    {
        if (generalFilter.at(i)->get_error_flag() < 0) return false;
    }
    return false;
}


void ClaseFourier::updateFilterSound()
{
    lfSamples = new Int16[buffer.getSampleCount()];
    double tempSample;
    switch (FiltroEscogido)
    {
        case 0:
            for (int i = 0; i < buffer.getSampleCount(); i++)
            {
                tempSample = (double)buffer.getSamples()[i];
                lfSamples[i] = lpfdataSample(tempSample);
            }
            cout << "Filtro de Low pass Aplicado!" << endl;
            break;
        case 1:
            for (int i = 0; i < buffer.getSampleCount(); i++)
            {
                tempSample = (double)buffer.getSamples()[i];
                lfSamples[i] = hpfdataSample(tempSample);
            }
            cout << "Filtro de High pass Aplicado!" << endl;
            break;
        case 2:
            for (int i = 0; i < buffer.getSampleCount(); i++)
            {
                tempSample = (double)buffer.getSamples()[i];
                lfSamples[i] = bpfdataSample(tempSample);
            }
            cout << "Filtro de Band pass Aplicado!" << endl;
            break;
    }

    fbuffer.loadFromSamples(lfSamples, buffer.getSampleCount(), buffer.getChannelCount(), buffer.getSampleRate());
    fsound.setBuffer(fbuffer);

}
Int16 ClaseFourier::lpfdataSample(double& s)
{
    return generalFilter.at(0)->do_sample((double)s);
}

Int16 ClaseFourier::hpfdataSample(double& s)
{
    return generalFilter.at(1)->do_sample((double)s);
}

Int16 ClaseFourier::bpfdataSample(double& s)
{
    return generalFilter.at(2)->do_sample((double)s);
}

void ClaseFourier::switchSource(bool s)
{
    if (!s)
    {
        fsound.setVolume(0.0f);
        sound.setVolume(100.0f);
    }
    else
    {
        sound.setVolume(0.0f);
        fsound.setVolume(100.0f);
    }
}

#endif //SOLUTION_FFT_H
