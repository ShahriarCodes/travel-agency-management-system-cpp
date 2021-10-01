//
// Created by sal on 30.09.21.
//

#include <iostream>
#include <unistd.h>
#include <set>
#include <cstring>
#include "cstdlib"
#include "vector"
#include "ctime"
#include "random"

using namespace std;

const int MAX_HEIGHT = 25;
const int MAX_WIDTH = 25;

const int TIGER = 1;
const int DEER = 2;
const int MONKEY = 3;
const int CAT = 4;
const int SNAKE = 5;

const int UP = 10;
const int DOWN = -10;
const int LEFT = -12;
const int RIGHT = 12;
const int ANY[4] = {UP, DOWN, LEFT, RIGHT};
const vector<int> CLOCK_WISE{DOWN, LEFT, UP, RIGHT};
const vector<int> COUNTER_CLOCK_WISE{UP, LEFT, DOWN, RIGHT};


int generateRandomNumberBetween(int low, int high) {
    // Random seed
    random_device rd;

    // Initialize Mersenne Twister pseudo-random number generator
    mt19937 gen(rd());

    // Generate pseudo-random numbers
    // uniformly distributed in range (1, 100)
    uniform_int_distribution<> dis(low, high);
    int random_num = dis(gen);
    return random_num;
}

int generateRandomDirection() {
    srand(time(nullptr));
    int random_number = ANY[rand() % 4];
    return random_number;
}

int determineNextAfterRandomDirection(int direction, const vector<int> CC_or_CCW) {
    int new_direction;

    for (int i = 0; i < CC_or_CCW.size(); i++) {
        if (CC_or_CCW[i] == direction) {
            if (i != CC_or_CCW.size() - 1) new_direction = CC_or_CCW[i + 1];
            else new_direction = CC_or_CCW[0];
        }
    }

    return new_direction;
}

vector<int> generateRandomPosition() {
    int i, j;
    vector<int> vec;

//    srand(time(nullptr));
//    i = rand() % MAX_HEIGHT - 1 + 1;
//    vec.push_back(i);
//
////    sleep(1);
//
//    srand(time(nullptr));
//    j = rand() % MAX_WIDTH - 1 + 1;
//    vec.push_back(j);

    i = generateRandomNumberBetween(1, MAX_HEIGHT);
    vec.push_back(i);
    j = generateRandomNumberBetween(1, MAX_WIDTH);
    vec.push_back(j);
    return vec;
}

class Position {
public:
    int new_i = 0, new_j = 0;
    int moves = 0;

    void moveUp(int i, int j, int steps) {
        this->new_i = i - steps;
        this->new_j = j;
        this->moves++;
    }

    void moveDown(int i, int j, int steps) {
        this->new_i = i + steps;
        this->new_j = j;
        this->moves++;
    }

    void moveLeft(int i, int j, int steps) {
        this->new_i = i;
        this->new_j = j - steps;
        this->moves++;
    }

    void moveRight(int i, int j, int steps) {
        this->new_i = i;
        this->new_j = j + steps;
        this->moves++;
    }

    vector<int> determineNewPosition(vector<int> initialPos, int steps, int direction) {
        vector<int> new_pos_vector;

        int i = initialPos[0];
        int j = initialPos[1];

        // if direction == up
        if (direction == 10) {
            moveUp(i, j, steps);

            // crossing the border then move reverse direction
            if (this->new_i < 1) {
                moveDown(i, j, steps);
            }
        } else if (direction == -10) {
            // if direction == down
            moveDown(i, j, steps);

            // crossing the border then move reverse direction
            if (this->new_i > MAX_HEIGHT - 1) {
                moveUp(i, j, steps);
            }
        } else if (direction == -12) {
            // if direction == left

            moveLeft(i, j, steps);
            // crossing the border then move reverse direction
            if (this->new_j < 1) {
                moveRight(i, j, steps);
            }
        } else if (direction == 12) {
            // if direction == right
            moveRight(i, j, steps);

            // crossing the border then move reverse direction
            if (this->new_j > MAX_WIDTH - 1) {
                moveLeft(i, j, steps);
            }
        }

        new_pos_vector.push_back(this->new_i);
        new_pos_vector.push_back(this->new_j);
        return new_pos_vector;
    }
};
//
//vector<int> determineNewPosition(vector<int> initialPos, int steps, int direction) {
//    int new_i, new_j;
//    vector<int> new_pos_vector;
//
//    int i = initialPos[0];
//    int j = initialPos[1];
//
//    // if direction == up
//    if (direction == 10) {
//        new_i = i - steps;
//        new_j = j;
//        // crossing the border
//        if(new_i < 1) {
//            // reverse direction
//            new_i = i + steps;
//            new_j = j;
//        }
//    } else if (direction == -10) {
//        // down
//        new_i = i + steps;
//        new_j = j;
//    } else if (direction == -12) {
//        // left
//        new_i = i;
//        new_j = j - steps;
//    } else if (direction == 12) {
//        // right
//        new_i = i;
//        new_j = j + steps;
//    } else {
//
//    }
//
//    new_pos_vector.push_back(new_i);
//    new_pos_vector.push_back(new_j);
//    return new_pos_vector;
//}


void board(vector<int> position) {
    int i_pos = position[0];
    int j_pos = position[1];

    for (int i = 0; i < MAX_HEIGHT; i++) {
        cout << "\t\t#";
        for (int j = 0; j < MAX_WIDTH - 2; j++) {
            if (i == 0 || i == MAX_HEIGHT - 1) cout << '#';
            else if (i == i_pos && j == j_pos) cout << 'T';
            else cout << " ";
        }
        cout << "#\n";
    }
}

class Tiger {
public:
    // i == y, j == x
    //    int current_i, current_j;
    Position tigerPosition = Position();
    vector<int> tigerInitialPos = generateRandomPosition();
    vector<int> tigerNewPos;
    bool dead = false;

    void moveTiger() {
        // tiger moves clockwise
        // vector<int> tigerInitialPos{10, 10};

        int randDir, nextDir;

        board(tigerInitialPos);

        randDir = generateRandomDirection();
        tigerNewPos = tigerPosition.determineNewPosition(tigerInitialPos, 5, randDir);
//        board(tigerNewPos);
//        sleep(1);

        nextDir = determineNextAfterRandomDirection(randDir, CLOCK_WISE);
        tigerNewPos = tigerPosition.determineNewPosition(tigerInitialPos, 2, nextDir);
//        board(tigerNewPos);
//        sleep(1);

//        board(tigerInitialPos);
//
//        randDir = generateRandomDirection();
//        tigerNewPos = determineNewPosition(tigerInitialPos, 5, randDir);
//        board(tigerNewPos);
//        sleep(1);
//
//        nextDir = determineNextAfterRandomDirection(randDir, CLOCK_WISE);
//        tigerNewPos = determineNewPosition(tigerInitialPos, 2, nextDir);
//        board(tigerNewPos);
//        sleep(1);

//    tigerNewPos = determineNewPosition(tigerInitialPos, 5, LEFT);
//    board(tigerNewPos);
//    sleep(1);
//
//    tigerNewPos = determineNewPosition(tigerInitialPos, 5, UP);
//    board(tigerNewPos);
//    sleep(1);
//
//    tigerNewPos = determineNewPosition(tigerInitialPos, 5, RIGHT);
//    board(tigerNewPos);
//    sleep(1);

    }
};


vector<char> stringSplit(string str, char del) {
    // declaring temp string to store the curr "word" upto del
    string temp = "";
    vector<string> vec;

    for (char i : str) {
        // If cur char is not del, then append it to the cur "word", otherwise
        // you have completed the word, print it, and start a new word.
        if (i != del) {
            temp += i;
        } else {
//            cout << temp << " ";
            vec.push_back(temp);
            temp = "";
        }
    }

//    cout << temp;
}

int main() {
    vector<vector<Tiger>> vec;

    for (int i = 0; i < MAX_HEIGHT; i++) {
        vector<Tiger> v1;
        v1.reserve(MAX_WIDTH);
        for (int j = 0; j < MAX_WIDTH; j++) {
            v1.emplace_back(Tiger());
        }
        vec.push_back(v1);
    }

    for (int i = 0; i < MAX_HEIGHT; i++) {

        for (int j = 0; j < MAX_WIDTH; j++) {
            cout << "(" << vec[i][j].tigerInitialPos[0] << "," << vec[i][j].tigerInitialPos[1] << ") ";
//            cout << vec[i][j].tigerInitialPos[0] << " ";
        }
        cout << "\n";
    }

    vector<vector<Tiger>> vec2 = vec;
    vector<string> string_vec;
    vector<vector<int>> pos_vec;

    //Cycling through the vec the first time.
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            // Cycling through the vec the second time
            for (int x = 0; x < MAX_HEIGHT; x++) {
                for (int y = 0; y < MAX_WIDTH; y++) {
                    if (i == x && j == y) { continue; }
                    if (vec[i][j].tigerInitialPos == vec[x][y].tigerInitialPos) {
                        printf("match [%d][%d] =  [%d][%d]", i, j, x, y);
                        vector<int> v1;
                        v1.push_back(i);
                        v1.push_back(j);
                        pos_vec.push_back(v1);
//                        string_vec.push_back(to_string(i) + "_" + to_string(j));
//                        string_vec.push_back(to_string(i) + "_" + to_string(j));
                    }
                }
            }
        }
    }

    int dead_count = 0;
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            if (vec[i][j].dead) dead_count++;
        }
    }

    cout << endl << "dead_count" << dead_count << endl;

    // make them dead
    for (auto it : pos_vec) {
        int i = it[0];
        int j = it[1];
        vec[i][j].dead = true;
    }

    dead_count = 0;
    for (int i = 0; i < MAX_HEIGHT; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            if (vec[i][j].dead) dead_count++;
        }
    }
    cout << "dead_count" << dead_count << endl;
}



//    int i = 0;
//    while (i < 100) {
//        int j = 0;
//        while (j < 100) {
//            cout << i << " ";
//            j++;
//        }
//        cout << endl;
//        i++;
//    }
//
//    system("clear");

//    vector<int> generatedPosition = generateRandomPosition();
//
//    int acc = 0;
//    while (acc < 2) {
//        cout << generatedPosition[acc] << " ";
//        acc++;
//    }

//    int arr[4] = {10, -10, 12, -12};
//    int acc = 0;
//    srand(time(nullptr));
//    while (acc < 100) {
//        cout << generateRandomNumber(arr) << endl;
//        sleep(1);
//        acc++;
//    }


//    board(10, 12);

//    cout << determineNextAfterRandomDirection(UP, CLOCK_WISE) << endl;
//    cout << determineNextAfterRandomDirection(RIGHT, CLOCK_WISE) << endl;
//    cout << determineNextAfterRandomDirection(DOWN, CLOCK_WISE) << endl;
//    cout << determineNextAfterRandomDirection(LEFT, CLOCK_WISE) << endl;

//    moveTiger();
//    moveTiger();
//    moveTiger();


//
//cout << endl << string_vec.size() << endl;
//// deleting duplicate from string
//set<string> const uniques(string_vec.begin(), string_vec.end());
//string_vec.assign(uniques.begin(), uniques.end());
//
//// print non duplicate string_vec
//for (auto i: string_vec) std::cout << i << ' ';
//
//cout << endl << string_vec.size() << endl;
//
//
////    for (string str: string_vec) {
////        string st = str;
////        vector<char> str_parsed = stringSplit(st, "_");
////        int i = str[0] - 48;
////
////
////        std::cout << i << endl;
////    }
//
////    for (int acc = 0; acc < string_vec.size(); acc++) {
////        string str = string_vec[acc];
////        char del = '_';
////        vector<char> str_parsed = stringSplit(str, del);
////        char char_i = str_parsed[0];
////        int i = ;
//////        int j = str_parsed[1] - 48;
////
////        std::cout << i << " " <<"" << endl;
////    }
////
////cout << atoi("12");
//
//
//// declaring temp string to store the curr "word" upto del
//// declaring temp string to store the curr "word" upto del
//auto temp = "";
//string del = "_";
//
//for(auto i=0; i<(int)string_vec[0].size(); i++){
//// If cur char is not del, then append it to the cur "word", otherwise
//// you have completed the word, print it, and start a new word.
//if(string_vec[0][i] != del){
//temp += string_vec[0][i];
//}
//else{
//cout << temp << " " << endl;
//temp = "";
//}
//}
//
//cout << temp;