#include "matrix.hpp"
#include "weights.hpp"
#include "learning.hpp"
#include "train.hpp"
#include "visual/history.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main(){
    int num;
    cout<<"how many times should it train?\n";
    cin>>num;
    train(num);
}