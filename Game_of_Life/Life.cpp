#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<string>
#include<cstring>
using namespace sf;


/*
g++ -c Life.cpp && 
g++ Life.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system &&
./sfml-app
*/


int n = 100;
//number of blocks on a side


int main(){

    RenderWindow appWindow(VideoMode(1000,800),"Langdon's Ant");
    Event appEvent;


    appWindow.setFramerateLimit(20);

    int size = 800/n;

    std::vector<std::vector<std::tuple<float,float,bool>>> grid(n);
    std::vector<std::pair<int,int>> neigh; 

    bool temp[n][n];
    memset(temp,false,sizeof(temp));

    neigh.push_back(std::make_pair(0,1));
    neigh.push_back(std::make_pair(1,0));
    neigh.push_back(std::make_pair(0,-1));
    neigh.push_back(std::make_pair(-1,0));

    neigh.push_back(std::make_pair(1,1));
    neigh.push_back(std::make_pair(1,-1));
    neigh.push_back(std::make_pair(-1,1));
    neigh.push_back(std::make_pair(-1,-1));


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
    int a,b;

        temp[10][10]=true;
        temp[10][11]=true;
        temp[10][12]=true;
        temp[9][12]=true;
        temp[8][11]=true;





    while(appWindow.isOpen()){
        while (appWindow.pollEvent(appEvent))
        {
            if(appEvent.type == Event::Closed)appWindow.close();
        }

        appWindow.clear(Color::Black);

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                rectangle.setPosition(std::get<0>(grid[i][j]),std::get<1>(grid[i][j]));
                std::get<2>(grid[i][j])=temp[i][j];
                if(std::get<2>(grid[i][j])==false){
                    rectangle.setFillColor(Color::White);
                }
                else{
                    rectangle.setFillColor(Color::Black);
                }
                rectangle.setOutlineColor(Color::Black);
                rectangle.setOutlineThickness(1);
                appWindow.draw(rectangle);
            }
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int c =0;
                for(int k=0;k<8;k++){
                    a = neigh[k].first;
                    b = neigh[k].second;

                    //std::cout<<neigh[k].first<<" "<<neigh[k].second<<"\n";
                    std::cout<<i+a<<" "<<j+b<<"\n";

                    if(i+a >=0 && i+a < n && j+b >=0 && j+b<n){
                        
                        if(std::get<2>(grid[i+a][j+b])==true){
                            c++;
                        }
                    }
                }
                std::cout<<c<<std::endl;
                if(c<2 || c>3)temp[i][j]=false;
                if(c==3)temp[i][j]=true;
                
            }
        }

        appWindow.display();
    }
    return 0;
}