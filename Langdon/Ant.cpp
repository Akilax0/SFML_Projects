#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<string>
using namespace sf;


/*
g++ -c Ant.cpp && 
g++ Ant.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system &&
./sfml-app
*/


int n = 100;
//number of blocks on a side


int main(){

    RenderWindow appWindow(VideoMode(800,800),"Langdon's Ant");
    Event appEvent;


    //appWindow.setFramerateLimit(2.5);

    int size = 800/n;

    std::vector<std::vector<std::tuple<float,float,bool>>> grid(n);

    float y=0;
    for(int i=0;i<n;i++){
        float x=0;
        for(int j=0;j<n;j++){
            grid[i].push_back(std::make_tuple(x,y,false));
            x +=size;
        }
        y +=size;
    }

    sf::RectangleShape rectangle(sf::Vector2f(size, size));
    int iter = 0;
    int posx=n/2,posy=n/2;
    int dir = 0;
    std::string filename = "";
    /*
    up    = 0
    right = 1 
    down  = 2 
    left  = 3
    */

    while(appWindow.isOpen()){
        while (appWindow.pollEvent(appEvent))
        {
            if(appEvent.type == Event::Closed)appWindow.close();
        }

        if(iter==11000){
            sf::Image screenshot =appWindow.capture();
            screenshot.saveToFile("screenshot.png");
            appWindow.close();
        }

        
        appWindow.clear(Color::Black);

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                rectangle.setPosition(std::get<0>(grid[i][j]),std::get<1>(grid[i][j]));
                if(std::get<2>(grid[i][j])==false){
                    rectangle.setFillColor(Color::White);
                }
                else{
                    rectangle.setFillColor(Color(125,125,125));
                }
                rectangle.setOutlineColor(Color::Black);
                rectangle.setOutlineThickness(1);
                appWindow.draw(rectangle);
            }
        }

        CircleShape ant;
        ant.setRadius(5);
        ant.setPosition(std::get<0>(grid[posx][posy])+size/2,std::get<1>(grid[posx][posy])+size/2);
        ant.setFillColor(Color::Red);
        appWindow.draw(ant);



            std::cout<<posx<<" "<<posy<<" "<<iter<<std::endl;
            iter++;
            if(std::get<2>(grid[posx][posy])==false){
                if(dir==0){
                    posy++;
                }
                else if(dir==1){
                    posx++;
                }
                else if(dir==2){
                    posy--;
                }
                else if(dir==3){
                    posx--;
                }
                dir = (dir+1)%4;
            }
            else{
                if(dir==0){
                    posy--;
                }
                else if(dir==1){
                    posx--;
                }
                else if(dir==2){
                    posy++;
                }
                else if(dir==3){
                    posx++;
                }
                dir = (dir+3)%4;
            }

            std::get<2>(grid[posx][posy])= !std::get<2>(grid[posx][posy]);


        

        appWindow.display();
    }
    return 0;
}