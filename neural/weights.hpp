#ifndef WEIGHTS
#define WEIGHTS
#include <vector>
#include "matrix.hpp"
#include "visual/history.hpp"
#include <fstream>
#include <random>
#include <string.h>
#include <iostream>
using namespace std;

inline vector<vector<vector<float>>> weights;
inline vector<vector<float>> biases;
inline float ALPHA=0.01f;

void instantiate(int depth,int nodeHeights[]){
    int inputSize=nodeHeights[0];
    int prev=inputSize;
    random_device rd;
    default_random_engine dre(rd());
    uniform_real_distribution<> urd(-1.0,1.0); 
    
    for(int i=1;i<depth+1;i++){
        int cur=nodeHeights[i];
        vector<vector<float>> tempM;
        vector<float> tempBV;
        for(int u=0;u<cur;u++){
            vector<float> tempV;
            for(int j=0;j<prev;j++){
                tempV.push_back(urd(dre));
            }
            tempBV.push_back(urd(dre));
            tempM.push_back(tempV);
        }
        weights.push_back(tempM);
        biases.push_back(tempBV);
        prev=cur;
    }
}
int setWeights(int inputHeight,int outputHeight){
    int time;
        try{
            ifstream fs ("weights.txt");
            fs>>time;
            string n;
            getline(fs,n);
            if (fs.eof()||time<1){
                eraseHistory();
                time=0;
                int depth;
                cout<<"input depth:\n";
                cin>>depth;
                int nodeHeights[depth+1];
                nodeHeights[0]=inputHeight;
                nodeHeights[depth]=outputHeight;
                cout<<"input inner neuron heights:\n";
                for(int i=1;i<depth;i++)
                    cin>>nodeHeights[i];
                instantiate(depth,nodeHeights);
            }
            else{
                string in;
                vector<float> tempV,
                tempBV;
                vector<vector<float>> tempM;
                char seps[]=",";
                while(!fs.eof()){
                    getline(fs,in);
                    if(in.empty()){
                        weights.push_back(tempM);
                        tempM.clear();
                        biases.push_back(tempBV);
                        tempBV.clear();
                        continue;
                    }
                    char *token;
                    token=strtok(&in[0],seps);
                    while( token != NULL )
                    {
                        tempV.push_back(stof(token));
                        token=strtok(NULL,seps);
                    }
                    tempBV.push_back(tempV[tempV.size()-1]);
                    tempV.pop_back();
                    tempM.push_back(tempV);
                    tempV.clear();
                }
            }
            fs.close();
        }
        catch (...){
            cout<<("File didn't open");
        }
        return time;
}
void updateWeights(int time){ 
    try{
        
        ofstream fs("weights.txt");
        fs<<++time<<"\n";
        for(int i=0;i<weights.size();i++){
            for(int u=0;u<weights[i].size();u++){
                for(int j=0;j<weights[i][u].size();j++)
                    fs<<weights[i][u][j]<<",";
                fs<<biases[i][u]<<",\n";
            }
            if(i+1!=weights.size())
                fs<<"\n";
        }
        fs.close();
    }
    catch(...){
        cout<<"file didn't open";
    }
}
#endif