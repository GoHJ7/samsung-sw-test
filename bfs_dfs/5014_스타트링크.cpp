#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int F,S,G,U,D;

const int MAX = 1000001;
bool visited[MAX];

int goToOffice(){
    queue<tuple<int,int>> q;

    q.push(make_tuple(S,0));

    while(!q.empty()){
        int curFloor, buttonPressed;

        tie(curFloor,buttonPressed) = q.front();
        q.pop();
        if(curFloor == G) return buttonPressed;
        if(curFloor + U <= F && !visited[curFloor + U]){
            q.push(make_tuple(curFloor + U, buttonPressed + 1));
            visited[curFloor + U] = true;
        }

        if(curFloor - D > 0 && !visited[curFloor - D]){
            q.push(make_tuple(curFloor -D, buttonPressed + 1));
            visited[curFloor - D] = true;
        }
    }
    return -1;
}

int main(){
    cin>>F>>S>>G>>U>>D;

    int output = goToOffice();
    if(output != -1) cout<<output;
    else cout<<"use the stairs";
}