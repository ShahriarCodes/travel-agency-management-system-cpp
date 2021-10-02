//
// Created by sal on 02.10.21.
//

#include <iostream>
using namespace std;
int main()
{
    ineligible:
    cout<<"You are not eligible to vote!\n";
    cout<<"Enter your age:\n";
    int age;
    if (!(cin>>age)) {
        goto ineligible;
    }
    if (age < 18){
        goto ineligible;
    }
    else
    {
        cout<<"You are eligible to vote!";
    }
}