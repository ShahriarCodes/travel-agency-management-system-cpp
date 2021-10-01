//
// Created by sal on 30.09.21.
//

#include <iostream>
#include <unistd.h>
#include "cstdlib"
#include "vector"
#include "ctime"

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

    srand(time(nullptr));
    i = rand() % MAX_HEIGHT - 1 + 1;
    vec.push_back(i);

    sleep(1);

    srand(time(nullptr));
    j = rand() % MAX_WIDTH - 1 + 1;
    vec.push_back(j);

    return vec;
}

class Position {
    int new_i, new_j;

    void moveUp(int i, int j, int steps) {
        this->new_i = i - steps;
        this->new_j = j;
    }

    void moveDown(int i, int j, int steps) {
        this->new_i = i + steps;
        this->new_j = j;
    }

    void moveLeft(int i, int j, int steps) {
        this->new_i = i;
        this->new_j = j - steps;
    }

    void moveRight(int i, int j, int steps) {
        this->new_i = i;
        this->new_j = j + steps;
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
            if (this->new_j > MAX_HEIGHT - 1) {
                moveUp(i, j, steps);
            }
        } else if (direction == -12) {
            // if direction == left

            moveLeft(i, j, steps);
            // crossing the border then move reverse direction
            if (this->new_i < 1) {
                moveRight(i, j, steps);
            }
        } else if (direction == 12) {
            // if direction == right
            moveRight(i, j, steps);

            // crossing the border then move reverse direction
            if (this->new_j > MAX_WIDTH - 1) {
                moveLeft(i, j, steps);
            }
        } else {

        }

        new_pos_vector.push_back(new_i);
        new_pos_vector.push_back(new_j);
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
    int current_i, current_j;

    void moveTiger() {
        // tiger moves clockwise
        // vector<int> tigerInitialPos{10, 10};
        vector<int> tigerInitialPos = generateRandomPosition();
        vector<int> tigerNewPos;
        int randDir, nextDir;

        board(tigerInitialPos);

        randDir = generateRandomDirection();
        tigerNewPos = determineNewPosition(tigerInitialPos, 5, randDir);
        board(tigerNewPos);
        sleep(1);

        nextDir = determineNextAfterRandomDirection(randDir, CLOCK_WISE);
        tigerNewPos = determineNewPosition(tigerInitialPos, 2, nextDir);
        board(tigerNewPos);
        sleep(1);

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


int main() {
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
}
