#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>

using namespace std;

bool convVisited[101];

int getManDistance(int sourceX,int sourceY, int destX, int destY){
    return abs(abs(sourceX - destX) + abs(sourceY - destY));
}
string areYouHappy(int houseX,int houseY,vector<tuple<int,int>>convCor,int pentaX,int pentaY){
    queue<tuple<int,int>> q;
    q.push(make_tuple(houseX,houseY));

    while(!q.empty()){
        int curX,curY;
        tie(curX,curY) = q.front();
        q.pop();
        cout<<curX<<curY<<endl;
        if(getManDistance(curX,curY,pentaX,pentaY)<=1000) return "happy";

        for(int i =0; i<convCor.size(); i++){
            if(getManDistance(curX,curY,get<0>(convCor[i]),get<1>(convCor[i])) <= 1000 
            && !convVisited[i]){
                convVisited[i] = true;
                q.push(convCor[i]);
            }
        }
    }
    return "sad";
}


int main(){
    int T;
    cin>>T;
    for(int i = 0; i<T; i++){
        int C;
        int houseX,houseY,pentaX,pentaY;
        vector<tuple<int,int>> convCor;
        int tempX,tempY;

        cin>>C;
        cin>>houseX>>houseY;
        for(int j = 0; j<C; j++){
            cin>>tempX>>tempY;
            convCor.push_back(make_tuple(tempX,tempY));
        }
        cin>>pentaX>>pentaY;
        cout<<areYouHappy(houseX,houseY,convCor,pentaX,pentaY)<<endl;
    }

}