#include "matrix.hpp"
#include "weights.hpp"
#include "learning.hpp"
#include "visual/history.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

void train(vector<float>& input,vector<float>& output){
    vector<vector<float>> neurons=forwardProp(input);
    //cout<<"neurons:";print(neurons);
    //cout<<"\nweights:";print(weights);
    weightUpdate(neurons,backwardProp(neurons,output));
    vector<float> out=neurons[neurons.size()-1];
    float cost=loss(out,output);
    updateHistory(cost);
    //cout<<"output: ";print(out);
    //cout<<"loss: "<<cost;
}
vector<float> breakup(string& in){
    vector<float> out;
    int i,index;
    for(i=0,index=0;i<in.length();i++)
        if(in[i]==','){
            out.push_back(stof(in.substr(index,i-index)));
            index=i+1;
        }
        out.push_back(stof(in.substr(index,i-index)));
    return out;
}
void train(int times){
    vector<vector<float>> input;
    vector<vector<float>> output;
    for(auto & entry : filesystem::directory_iterator("input")){
        try{
            string file =entry.path().string();
            string extracts;
            ifstream ifs(file);
            ifs>>extracts;
            input.push_back(breakup(extracts));
            ifs>>extracts;
            output.push_back(breakup(extracts));
            ifs.close();
        }
        catch(...){
            cout<<"file error\n";
        }
    }
    int time=setWeights(input[0].size(),output[0].size());
    for(int i=0;i<times;i++)
        for(int u=0;u<input.size();u++)
            train(input[u],output[u]);
    updateWeights(times*input.size()+time);
}