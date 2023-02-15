#ifndef LEARNING
#define LEARNING
#include "matrix.hpp"
#include "weights.hpp"
#include <vector>
#include <iostream>
using namespace std;

vector<vector<float>> forwardProp(vector<float> input){
    vector<vector<float>> neurons;
    neurons.push_back(input);
    for(int i=0;i<weights.size();i++){
        input=add(mult(weights[i],input),biases[i]);
        neurons.push_back(leakyReLu(input));
    }
    return neurons;
}
vector<vector<float>> backwardProp(const vector<vector<float>>& neurons,const vector<float>& expected){
    int depth=weights.size();
    vector<vector<float>> errors;
    errors.resize(depth);
    vector<float> dif=subtract(neurons[depth],expected),
    prime=lrPrime(neurons[depth]);
    //print(dif);cout<<" o ";print(prime);
    errors[depth-1]=(hadamardProduct(dif,prime));
    for(int i=depth-1;i>0;i--){
        dif=mult(transpose(weights[i]),errors[i]);
        prime=lrPrime(neurons[i]);
        //print(dif);cout<<" o ";print(prime);
        errors[i-1]=hadamardProduct(dif,prime);
    }
    //cout<<"errors: ";print(errors);cout<<"end\n";
    return errors;
}
void weightUpdate(const vector<vector<float>>& neurons,const vector<vector<float>>& errors){
    for(int i=0;i<weights.size();i++){
        vector<vector<float>> dif=outerProduct(errors.at(i),neurons.at(i)),
        delta=mult(dif,ALPHA);
        weights[i]=subtract(weights[i],delta);
        biases[i]=subtract(biases[i],errors[i]);
    }
}
float loss(vector<float> output,vector<float> expected){
    float sum=0.0f;
    for(int i=0;i<output.size();i++){
        float dif=output[i]-expected[i];
        sum+=dif*dif;
    }
    return sum/2; 
}
#endif