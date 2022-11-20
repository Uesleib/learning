#include<stack>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;


class Coordinates{
    public:
    int x;
    int y;

    Coordinates(){

        x = 0;
        y = 0;
    }
    Coordinates(int i,int j){
        x = i;
        y = j;
    }
};

class Node2D{
    public:

    bool wallTop, wallBottom, wallRight, wallLeft;
    bool visited;
    Coordinates coordinates;

    Node2D(){
        wallBottom = true;
        wallTop = true;
        wallRight = true;
        wallLeft = true;
        visited = false;
    }

    void set_coordinates(int i, int j){
        coordinates.x=i;
        coordinates.y=j;
    }
};


class Maze{
    private:
        Node2D **grid;
        int height, width;
    public:

    Maze(int x, int y){
        height=x;
        width=y;

        grid= new Node2D*[height];
        for(int i=0; i<height ; i++){
            grid[i]=new Node2D [width];
            for(int j=0; j< width; j++){
                // grid[i][j].wallTop=true;
                // grid[i][j].wallBottom=true;
                // grid[i][j].wallRight=true;
                // grid[i][j].wallLeft=true;
                // // grid[i][j].wall_
                // // grid[i][j].wall_
                // grid[i][j].visited=false;
                grid[i][j].set_coordinates(i,j);
            }
        }

    }

    void digMaze(){
        stack<Coordinates> backtraking;

        Coordinates currentCoords(0,0);
        backtraking.push(grid[0][0].coordinates);
        grid[0][0].visited=true;
        grid[0][0].wallTop = false;

        // Seed for random number generator
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        int  interations=0;
        int visited=0;
        while(!backtraking.empty()  ){
            int numberAdjacentVisited=0;
            int adjacentVisited[4];
            
            cout<<"interation: "<< ++interations<<endl;
            print_grid();
            cout<<"Currente cords: "<<currentCoords.x<<" "<<currentCoords.y<<endl;
            
            if(currentCoords.x<height-1){
                cout<<"to down"<<endl;
                if(grid[currentCoords.x + 1][currentCoords.y].visited == false ){
                    adjacentVisited[numberAdjacentVisited]=0;
                    numberAdjacentVisited++;    
                    cout<<"down added"<<endl;
                }
            }

            if(currentCoords.x>0){
                cout << "to up" << endl;
                if (grid[currentCoords.x - 1][currentCoords.y].visited == false)
                {
                    adjacentVisited[numberAdjacentVisited] = 1;
                    numberAdjacentVisited++;
                    cout << "up added" << endl;
                }
            }
            if(currentCoords.y<width-1){
                cout << "to right" << endl;
                if (grid[currentCoords.x][currentCoords.y + 1].visited == false)
                {
                    adjacentVisited[numberAdjacentVisited] = 2;
                    numberAdjacentVisited++;
                    cout << "right added" << endl;
                }
            }

            if (currentCoords.y > 0)
            {
                cout << "to left" << endl;
                if (grid[currentCoords.x][currentCoords.y - 1].visited == false)
                {
                    adjacentVisited[numberAdjacentVisited] = 3;
                    numberAdjacentVisited++;
                    cout << "left added" << endl;
                }
            }            

            cout<<"Number visited:"<<numberAdjacentVisited<<endl;
            if(numberAdjacentVisited==0){
                cout<<"backtraking\n";
                backtraking.pop();
                if(!backtraking.empty())
                    currentCoords=backtraking.top();
            }else{
                uniform_int_distribution<int> distribution(0, numberAdjacentVisited-1);

                int next_node=adjacentVisited[distribution(generator)];                
                cout<< next_node<<endl;
                if(next_node==0){
                    grid[currentCoords.x][currentCoords.y].wallBottom=false;

                    currentCoords.x++;

                    cout<< "down " << currentCoords.x << " " << currentCoords.y << endl;
                    backtraking.push(currentCoords);
                    grid[currentCoords.x][currentCoords.y].wallTop = false;
                    grid[currentCoords.x][currentCoords.y].visited = true;
                }
                else if (next_node == 1)
                {
                    grid[currentCoords.x][currentCoords.y].wallTop = false;

                    currentCoords.x--;

                    cout << "up " << currentCoords.x << " " << currentCoords.y << endl;
                    backtraking.push(currentCoords);
                    grid[currentCoords.x][currentCoords.y].wallBottom = false;
                    grid[currentCoords.x][currentCoords.y].visited = true;
                }
                else if (next_node == 2)
                {
                    grid[currentCoords.x][currentCoords.y].wallRight = false;

                    currentCoords.y++;
                    cout << "right " << currentCoords.x << " " << currentCoords.y << endl;
                    backtraking.push(currentCoords);
                    grid[currentCoords.x][currentCoords.y].wallLeft = false;
                    grid[currentCoords.x][currentCoords.y].visited = true;
                }
                else if (next_node == 3)
                {   
                    grid[currentCoords.x][currentCoords.y].wallLeft = false;

                    currentCoords.y--;
                    cout << "left " << currentCoords.x << " " << currentCoords.y << endl;

                    backtraking.push(currentCoords);
                    grid[currentCoords.x][currentCoords.y].wallRight = false;
                    grid[currentCoords.x][currentCoords.y].visited = true;
                }
            }
            }
    }


    void print_grid(){

        int i,j;

        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                cout << "_"; 
                grid[i][j].wallTop? cout<<"_":cout<<" ";  
                cout<< "_";
            }
            cout << endl;

            for (j = 0; j < width; j++)
            {
                grid[i][j].wallLeft? cout<<"|" : cout<<" "; 
                grid[i][j].visited? cout<<" ":cout<<".";
                grid[i][j].wallRight ? cout << "|" : cout << " ";
            }
            cout << endl;
            for (j = 0; j < width; j++)
            {
                cout << "_";
                grid[i][j].wallBottom ? cout << "_" : cout << " ";
                cout<< "_";
            }
            cout << endl;
        }
    }
    void create_pbm(){
        ofstream pbm("maze.pbm");
        int i,j;
        pbm<<"P1\n";
        pbm<<width*3<<" "<<height*3<<endl;

        for(i=0; i<height;i++){
            for(j=0;j<width; j++){
                pbm<<"1 "<<grid[i][j].wallTop<<" 1 ";
            }
            pbm<<endl;

            for (j = 0; j < width; j++)
            {
                pbm << grid[i][j].wallLeft<<" " << !grid[i][j].visited<<" " << grid[i][j].wallRight<<" ";
            }
            pbm << endl;
            for (j = 0; j < width; j++)
            {
                pbm << "1 " << grid[i][j].wallBottom << " 1 ";
            }
            pbm << endl;
        }

    }
};



int main(int argc, char **argv){
    int height= atoi(argv[1]);
    int width= atoi(argv[2]);

    Maze maze(height, width);

    // maze.print_grid();
    maze.digMaze();

    maze.create_pbm();

    return 0;
}