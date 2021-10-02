//
// Created by sal on 02.10.21.
//

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define CLOCKWISE 1
#define ANTI_CLOCKWISE 2

#define TIGER 0
#define DEER 1
#define MONKEY 2
#define CAT 3
#define SNAKE 4

int move_count[5];

int reverse(int direction)//revereses the direcrtion
{
    if(direction == UP)return DOWN;
    if(direction == DOWN)return UP;
    if(direction == LEFT)return RIGHT;
    return LEFT;
}
int rotate(int direction,int clock)//rotates clockwise and anticlockwise
{
    int ans;
    if(direction == UP||direction == DOWN)
    {
        if(clock == CLOCKWISE)ans=RIGHT;
        else ans = LEFT;
        if(direction == DOWN)ans = reverse(ans);
    }
    else if(direction == LEFT || direction == RIGHT)
    {
        if(clock == CLOCKWISE)ans=UP;
        else ans = DOWN;
        if(direction == RIGHT)ans = reverse(ans);
    }
    return ans;
}
class Animal
{
protected:

    int pos_x;
    int pos_y;
    int current_direction;
    int type;
public:

    Animal()
    {
        //construtor
        pos_x = rand()%100;
        if(pos_x==0)pos_x=100;

        pos_y = rand()%100;
        if(pos_y==0)pos_y=100;
        //generates randoms between 1 and 100

        current_direction = rand() % 4;
        if(current_direction == 0)current_direction = 4;

        //random direction in 4 areas

    }
    void move()
    {
        if(type == TIGER)
        {
            for(int i=0;i<5;i++)
            {
                increment();
            }
            current_direction = rotate(current_direction,CLOCKWISE);
            increment();
            increment();
        }
        else if(type == DEER)
        {
            for(int i=0;i<6;i++)
            {
                increment();
            }
            current_direction = rotate(current_direction,ANTI_CLOCKWISE);
            increment();
            increment();
            increment();
        }
        else if(type == MONKEY)
        {
            for(int i=0;i<7;i++)
            {
                increment();
            }
            current_direction = rotate(current_direction,CLOCKWISE);
            increment();
        }
        else if(type == CAT)
        {
            for(int i=0;i<2;i++)
            {
                increment();
            }
            current_direction = rotate(current_direction,ANTI_CLOCKWISE);
            increment();
        }
        else
        {
            for(int i=0;i<2;i++)
            {
                increment();
            }
            int prev_direction = current_direction;
            current_direction = rotate(current_direction,CLOCKWISE);
            increment();
            current_direction = prev_direction;
            increment();
            increment();
            current_direction = rotate(current_direction,ANTI_CLOCKWISE);
            increment();
        }
    }

    void increment()//function that moves
    {
        if(current_direction == UP)
        {
            if(pos_y-1>=1)pos_y--;//not bordering
            else
            {
                current_direction = reverse(current_direction);
                increment();
            }
            return;
        }
        if(current_direction == DOWN)
        {
            if(pos_y+1<=100)pos_y++;
            else
            {
                current_direction = reverse(current_direction);
                increment();
            }
            return;
        }
        if(current_direction == LEFT)
        {
            if(pos_x-1>=1)pos_x--;
            else
            {
                current_direction = reverse(current_direction);
                increment();
            }
            return;
        }
        if(current_direction == RIGHT)
        {
            if(pos_x+1<=100)pos_x++;
            else
            {
                current_direction = reverse(current_direction);
                increment();
            }
            return;
        }

    }
    void set_type(int t)//setter method
    {
        type = t;
    }
    int get_pos_x()//getter method
    {
        return pos_x;//safety so no one can modify
    }
    int get_pos_y()
    {
        return pos_y;
    }
    int get_current_direction()
    {
        return current_direction;
    }
    int get_type()
    {
        return type;
    }

};
class Tiger : public Animal
{

};

class Deer : public Animal
{

};

class Monkey : public Animal
{

};

class Cat : public Animal
{

};

class Snake : public Animal
{

};
class Simulation
{
    //will contain all the animals
    //will eliminate the colliding animals
private:
    bool running;//true means its playing
    int round;
public:
    vector<Animal> animals;
    string fileCopy;
    bool get_running()
    {
        return running;
    }
    Simulation()//constructor
    {
        //create each type animal of random quantity
        ofstream o;
        string output = "Round\tTiger\tDeer\tMonkey\tCat\tSnake\n";
        o.open("livingAnimals.txt");
        o << output;
        o.close();
        //this part outputs the head part of textfile
        int x;
        round = 1;//round starts as first round
        running = true;
        for(int i=0;i<5;i++)
        {
            x = rand()%100;
            if(x==0)x=100;
            //how many Tiger, deer, cat,snake, monkey
            Animal a;
            while(x--)
            {
                switch(i)
                {
                    case 0 : a = Tiger();
                        a.set_type(TIGER);
                        break;
                    case 1 : a = Deer();
                        a.set_type(DEER);
                        break;
                    case 2 : a = Monkey();
                        a.set_type(MONKEY);
                        break;
                    case 3 : a = Cat();
                        a.set_type(CAT);
                        break;
                    default :
                        a = Snake();
                        a.set_type(SNAKE);
                }
                animals.push_back(a);
                //cout << a.get_type() << endl;
            }
        }

    }
    vector<int> list_duplicate(int i)//returns the list of index which have same x,y position
    {
        //finds all the index of animals with same coordinate as
        // ith animal
        vector<int> ans;
        for(int q=(int)animals.size()-1;q >= i ; q--)
        {
            if(animals[q].get_pos_x() == animals[i].get_pos_x() &&
               animals[q].get_pos_y() == animals[i].get_pos_y())
            {
                ans.push_back(q);
            }
        }
        return ans;
    }
    void remove_duplicates()
    {
        vector<int> temp_list;
        if(animals.size()<2)running=false;

        for(int i=0; i < (int)animals.size(); i++)
        {
            if((int)animals.size() <= 1)running = false;
            temp_list = list_duplicate(i);
            if((int)temp_list.size() > 1)
            {
                for(int q=0;q<(int)temp_list.size();q++)animals.erase(animals.begin()+temp_list[q]);
                i--;
            }
        }
        //traverses all the animals and runs the list duplicate option, and deletes animals
        //delete right to left to avoid collision
    }
    void play()
    {
        remove_duplicates();
        print_to_file();
        for(int i=0;i<(int)animals.size();i++)
        {
            animals[i].move();
        }
        round++;
        if(round > 100)running=false;
    }
    string make_line()
    {
        string g = "";
        string h;
        stringstream ss;//string stream
        ss << round;
        ss >> h;
        g+=h;
        g+='\t';//tab 4 space

        int animal_count[5];
        for(int q=0;q<5;q++)animal_count[q]=0;
        for(int i=0;i<(int)animals.size(); i++)
        {
            animal_count[animals[i].get_type()]++;
        }
        for(int q=0;q<5;q++)
        {
            stringstream gg1;
            gg1<<animal_count[q];
            gg1>>h;
            g+=h;
            g+='\t';
        }
        g+='\n';
        return g;

    }
    void print_to_file()
    {
        fstream ip;
        ip.open("livingAnimals.txt",fstream::in);
        string g;
        vector<int> temp;
        int x;
        stringstream ss;
        fileCopy = "";
        while(getline(ip,g))
        {
            fileCopy += g;
            fileCopy+='\n';
        }
        ip.close();
        fileCopy+=make_line();
        ofstream of;
        of.open("livingAnimals.txt");
        of<<fileCopy;
        of.close();

        //extract string from file
        //print new line
        //close
    }


};

int main()
{
    srand(time(0));
    Simulation a = Simulation();
    while(a.get_running())
    {
        a.play();
    }
    return 0;
}