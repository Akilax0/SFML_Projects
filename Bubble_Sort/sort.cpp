#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

//part is the phase 
    //generating random heights
    //ordering them
int randomh = 0, part = 1;
int itera=0;
int major=0,count=0,lims=799;


struct data{
    int height;
    int posx;
}line[800];

/*
g++ -c sort.cpp && 
g++ sort.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system &&
./sfml-app
*/

int main(){
    RenderWindow appWindow( VideoMode(800,600), "Bubble sort");
    appWindow.setFramerateLimit(0);
    Event appEvent;

    Texture fondot;
    fondot.loadFromFile("fondo1.png");
    Sprite fondo(fondot);

    RectangleShape rectangle(Vector2f(2,178));
    rectangle.setFillColor(Color(235,149,13));



    Clock clock;

//prevents sequence repetition
    srand(time(NULL));

    while(appWindow.isOpen()){
        while(appWindow.pollEvent(appEvent)){
            if(appEvent.type == Event::Closed)appWindow.close();
        }
        if(part==2){
            if(line[itera].height < line[itera+1].height){
                major = line[itera].height;
                line[itera].height = line[itera+1].height;
                line[itera+1].height = major;
            }
        }

        if(part==1){
            for(int i=0;i<800;i++){
                randomh = 1 + rand()%(600);
                line[i].posx = i;
                line[i].height = randomh;
                if(i==799)part=2;
            }
        }

        appWindow.clear(Color::Black);
        appWindow.draw(fondo);
        for(int i=0;i<800;i++){
            rectangle.setFillColor(Color(235,149,13));
            if(i==itera)rectangle.setFillColor(Color(255,0,0));
            rectangle.setPosition(line[i].posx,600);
            rectangle.setSize(Vector2f(2,line[i].height));
            rectangle.setRotation(180);
            appWindow.draw(rectangle);
        }

        Time time = clock.getElapsedTime();
        std::cout<<1.0f / time.asSeconds() <<std::endl;

        appWindow.display();
        itera++;
        if(itera>=lims){
            itera = 0 ;
            count++;
            lims--;
        }
    }

    return 0;
}