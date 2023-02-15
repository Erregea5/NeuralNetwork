#ifndef HISTORY
#define HISTORY

#include <fstream>
#include <iostream>
using namespace std;

void updateHistory(float cost){
    try{
        ofstream ofs("visual\\history.txt",ios::app);
        ofs<<cost<<"\n";
        ofs.close();
        //cout<<"closed\n";
    }
    catch(...){
        cout<<"error opening file";
    }
}
void eraseHistory(){
    try{
        ofstream ofs("visual\\history.txt",ios::trunc);
        ofs<<"";
        ofs.close();
        //cout<<"deleted\n";
    }
    catch(...){
        cout<<"error opening file";
    }
}
#endif