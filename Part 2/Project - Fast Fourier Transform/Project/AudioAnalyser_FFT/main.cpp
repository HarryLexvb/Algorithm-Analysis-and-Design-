/*Author: Harold Alejandro Villanueva Borda
 * Date: 20/06/2022
 * Department: Computer Science
 * Curse: Algorithm Analysis and Design
 * Institution: San Pablo Catholic University of Arequipa
*/

#include "analyser.h"

const int WINDOW_X = 600;
const int WINDOW_Y = 600;
const int WINDOW_FPS = 60;
const int TEXTURE_X = 0.8*WINDOW_X;
const int TEXTURE_Y = 0.35*WINDOW_Y;
const std::string FILENAME = "Naruto.wav";


int main(){
    analyser ana(R"(C:\Users\win 10\Documents\CLION\AudioAnalyser_FFT\sounds\)" + FILENAME);
    ana.mapBuffer(TEXTURE_Y/2, -TEXTURE_Y/2);
    int dur = ana.duration.asSeconds();


    //Main Window Components
    sf::RenderWindow win(sf::VideoMode(WINDOW_X, WINDOW_Y), FILENAME);
    win.setFramerateLimit(WINDOW_FPS);

    sf::Event ev;                                               //Event Handler


    //Timeline components
    sf::RectangleShape timeline(sf::Vector2f(TEXTURE_X, 1));
    timeline.setFillColor(sf::Color::Black);
    timeline.setPosition((WINDOW_X-TEXTURE_X)/2, 0.9*WINDOW_Y);
    //Seek
    sf::CircleShape seek(3);
    seek.setPointCount(64);
    seek.setOrigin(3,3);
    seek.setFillColor(sf::Color::Black);

    //Graph components
    sf::Vertex vertices[TEXTURE_X];
    for (int i=0; i<TEXTURE_X; i++){
        vertices[i].position.y = TEXTURE_Y/2;
        vertices[i].color = sf::Color(0,0,0,i*255/TEXTURE_X);
    }

    sf::VertexBuffer vb(sf::LineStrip);
    vb.create(TEXTURE_X);


    //Render texture components
    sf::RenderTexture rendergraph;
    rendergraph.create(TEXTURE_X, TEXTURE_Y);
    sf::Sprite graph;
    graph.setTexture(rendergraph.getTexture());
    graph.setPosition((WINDOW_X-TEXTURE_X)/2, (WINDOW_Y-TEXTURE_Y)*0.2);


    ana.sound.play();

    while(win.isOpen()){

        while(win.pollEvent(ev)){
            if (ev.type == 0 || (ev.type == 5 && ev.key.code == 36))
                win.close();
            else if(ev.type == 5 && ev.key.code == 57){
                if(ana.sound.getStatus()==2)
                    ana.sound.pause();
                else
                    ana.sound.play();
            }
        }



        //Update vertex buffer
        for(int i=0; i<TEXTURE_X; i++)
            vertices[i].position = sf::Vector2f(i, vertices[i+1].position.y);

        vertices[TEXTURE_X-1].position = sf::Vector2f(TEXTURE_X-1, TEXTURE_Y/2+ana.getHeight());

        vb.update(vertices);




        int now_sec = ana.sound.getPlayingOffset().asSeconds();
        int pos = (WINDOW_X-TEXTURE_X)/2+now_sec*TEXTURE_X/dur;
        seek.setPosition(pos,WINDOW_Y*0.9);

        rendergraph.clear(sf::Color::White);
        rendergraph.draw(vb);


        win.clear(sf::Color::White);
        win.draw(graph);
        win.draw(timeline);
        win.draw(seek);
        win.display();
    }
}