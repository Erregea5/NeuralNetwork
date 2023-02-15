#ifndef MATRIX
#define MATRIX
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

float sigmoid(float x){
    return 1.0 / (1.0 + exp(-x));
}
vector<float> sigmoid(vector<float> x){
    vector<float> out;
    for (float i:x)
        out.push_back(sigmoid(i));
    return out;
}
vector<float> sPrime(vector<float> x){
    vector<float> out;
    vector<float> sig=sigmoid(x);
    for(float s:sig)
        out.push_back(sigmoid(1-s));
    return out;
}
float reLu(float x){
    return x>0? x:0;
}
vector<float> reLu(vector<float> x){
    vector<float> out;
    for (float i:x)
        out.push_back(reLu(i));
    return out;
}
vector<float> rPrime(vector<float> x){
    vector<float> out;
    for(float i:x)
        out.push_back(i>0?1:0);
    return out;
}
float leakyReLu(float x){
    return x>0? x: .1f*x;
}
vector<float> leakyReLu(vector<float> x){
    vector<float> out;
    for (float i:x)
        out.push_back(leakyReLu(i));
    return out;
}
vector<float> lrPrime(vector<float> x){
    vector<float> out;
    for(float i:x)
        out.push_back(i>0?1:.1f);
    return out;
}
float magnitude(vector<float> x){
    float sqr=0;
    for(float i:x)
        sqr+=i*i;
    return sqrt(sqr);
}


vector<vector<float>> transpose(vector<vector<float>> mat){
    vector<vector<float>> out;
    for (int j = 0; j < mat[0].size(); j++){
        vector<float> temp;
        for (int i = 0; i < mat.size(); i++)
            temp.push_back(mat[i][j]);
        out.push_back(temp);
    }
    return out;
}
vector<vector<float>> transpose(vector<float> vec){
    vector<vector<float>> out;
    for(int i=0;i<vec.size();i++){
        vector<float> temp;
        temp.push_back(vec[i]);
        out.push_back(temp);
    }
    return out;
}


vector<float> add(vector<float> left, vector<float> right, bool negative=0){
    vector<float> out;
    for (int i = 0; i < left.size(); i++)
        out.push_back(negative ? left[i] - right[i] : left[i] + right[i]);
    return out;
}
vector<vector<float>> add(vector<vector<float>> left, vector<vector<float>> right, bool negative=0){
    vector<vector<float>> out;
    for (int i = 0; i < left.size(); i++){
        vector<float> temp;
        for (int j = 0; j < left[i].size(); j++)
            temp.push_back(negative ? left[i][j] - right[i][j] : left[i][j] + right[i][j]);
        out.push_back(temp);
    }
    return out;
}
vector<float> subtract(vector<float> left, vector<float> right){
    return add(left,right,true);
}
vector<vector<float>> subtract(vector<vector<float>> left, vector<vector<float>> right){
    return add(left,right,true);
}


float dotProduct(vector<float> left, vector<float> right){
    float sum = 0;
    for (int i = 0; i < left.size(); i++)
        sum += (left[i] * right[i]);
    return sum;
}
vector<vector<float>> outerProduct(vector<float> left,vector<float> right){
    vector<vector<float>> out;
    for(float l:left){
        vector<float> temp;
        for(float r:right)
            temp.push_back(l*r);
        out.push_back(temp);
    }
    return out;
}
vector<float> hadamardProduct(vector<float> left, vector<float> right){
    vector<float> out;
    for (int i = 0; i < left.size(); i++)
        out.push_back(left[i]*right[i]);
    return out;
}
vector<vector<float>> hadamardProduct(vector<vector<float>> left, vector<vector<float>> right){
    vector<vector<float>> out;
    for (int i = 0; i < left.size(); i++)
        out.push_back(hadamardProduct(left[i], right[i]));
    return out;
}


vector<vector<float>> mult(vector<vector<float>> left, vector<vector<float>> right){
    vector<vector<float>> out;
    right = transpose(right);
    for (int i = 0; i < left.size(); i++){
        vector<float> temp;
        for (int k = 0; k < right.size(); k++)
            temp.push_back(dotProduct(right[k], left[i]));
        out.push_back(temp);
    }
    return out;
}
vector<float> mult(vector<vector<float>> left, vector<float> right){
    vector<float> out;
    for (int i = 0; i < left.size(); i++){
        out.push_back(dotProduct(left[i],right));
        //cout<<"dp: "<<dotProduct(left[i],right)<<endl;
    }
    return out;
}
vector<vector<float>> mult(vector<vector<float>> left, float right){
    for (int i = 0; i < left.size(); i++)
        for (int j = 0; j < left[0].size(); j++)
            left[i][j]*=right;
    return left;
}


void print(vector<float> in){
    cout<<"{";
    for(float i:in)
        cout<<i<<",";
    cout<<"}"<<endl;
}
void print(vector<vector<float>> in){
    cout<<"{"<<endl;
    for(vector<float> i:in)
        print(i);
    cout<<"}"<<endl;
}
void print(vector<vector<vector<float>>> in){
    cout<<"{"<<endl;
    for(vector<vector<float>> i:in)
        print(i);
    cout<<"}"<<endl;
}

#endif