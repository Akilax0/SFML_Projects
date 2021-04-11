#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<math.h>
using namespace sf;

/*
g++ -c Sales.cpp && 
g++ Sales.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system &&
./sfml-app
*/

int n = 15;
int r = 5;
int iter = 1,curr=0;
int index = 0;
struct stats
{
    int x;
    int y;

}cities[100];




int main(){

    RenderWindow appWindow(VideoMode(800,600),"Sales");
    Event appEvent;
    appWindow.setFramerateLimit(2);

    bool visited[n];
    std::pair<int,float> mi;
    mi.first  = 0;
    mi.second = 480000;
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    visited[0]=true;
    Vertex final[n];
   
    bool flag = false;
    CircleShape city;
    city.setRadius(r);
    city.setOutlineColor(sf::Color::White);
    city.setOutlineThickness(2);
    city.setPosition(10, 20);

    srand(time(NULL));

    for(int i=0;i<n;i++){
        cities[i].x = 100 + rand()%600;
        cities[i].y = 100 + rand()%400;
    }

    float matrix[n][n];
    float memo[n][n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            memo[i][j]=NULL;
            if(i==j){
                matrix[i][j]=0;
            }
            else{
                
                float dis=sqrt(pow(abs(cities[i].x-cities[j].x),2) + pow(abs(cities[i].y-cities[j].y),2));
                matrix[i][j] = dis;
                matrix[j][i] = dis;
            }
        }
    }

    








    final[index]=Vertex(Vector2f(cities[curr].x+r,cities[curr].y+r),Color::Yellow);


    while(appWindow.isOpen()){
        while (appWindow.pollEvent(appEvent))
        {
            if(appEvent.type == Event::Closed)appWindow.close();
        }


        appWindow.clear(Color::Black);
       
        for(int i=0;i<n;i++){
            city.setPosition(cities[i].x,cities[i].y);
            appWindow.draw(city);
        }


/*
        if(flag==false){
            if(iter<n && visited[iter]==false){
                std::cout<<curr<<" "<<iter<<std::endl;
                Vertex line[] ={Vertex(Vector2f(cities[curr].x+r,cities[curr].y+r),Color::White),Vertex(Vector2f(cities[iter].x+r,cities[iter].y+r),Color::White)};
                float dis = sqrt(pow(abs(cities[curr].x-cities[iter].x),2) + pow(abs(cities[curr].y-cities[iter].y),2));
                if(dis<mi.second){
                    mi.first = iter;
                    mi.second = dis;
                }
                appWindow.draw(line, 2,Lines);
            }
            iter++;

            if(iter==n){
                curr = mi.first;
                visited[curr]=true;
                mi.second = 480000;
                iter = 0;
                index++;
                final[index]=Vertex(Vector2f(cities[curr].x+r,cities[curr].y+r),Color::Yellow);
            }
        }
*/
        for(int i=0;i<index;i++){
            Vertex line[] = {final[i],final[i+1]};
            appWindow.draw(line, 2,Lines);
        }

        if(index == n-1){
            flag=true;
            Vertex line[] = {final[index],final[0]};
            appWindow.draw(line, 2,Lines);
        }
        appWindow.display();
    }
    return 0;
}