

#include<iostream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

typedef struct atom{
    int x;
    int y;
    int energy;
    int dir;
}Atom;

Atom atom[1001];
int exploded[1001];
int dirX[4] = {0,0,-1,1};
int dirY[4] = {1,-1,0,0};
typedef pair<int,pair<int,int>> expair;
class compare{
    public:
    bool operator()(const expair& a, const expair& b){
        if(a.first == b.first){
            if(atom[a.second.first].x == atom[a.second.second].x
            || atom[a.second.first].y == atom[a.second.second].y) return true;
            else return false;
        }else{
            return a.first > b.first;
        }
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int n;
        cin>>n;
        //time, atomN, atomN
        priority_queue<expair,vector<expair>,compare> pq;
        memset(exploded,0,sizeof(exploded));
        int totalE = 0;
        for(int i = 0; i < n ; i++){
            cin>>atom[i].x>>atom[i].y>>atom[i].dir>>atom[i].energy;
        }

        for(int i =0; i < n ; i++){
            for(int j = i; j< n; j++){
                if(i == j) continue;

                //충동 시나리오 | 같은 열 혹은 행, 역방향 | dir* dx + x, dir*dy 가 서로 같음
                if(atom[i].x == atom[j].x){
                    if(atom[i].y>atom[j].y &&  atom[i].dir == 1 && atom[j].dir == 0){
                        int time = abs(atom[i].y - atom[j].y);
                        pq.push(make_pair(time,make_pair(i,j)));
                    }else if(atom[i].y<atom[j].y &&  atom[i].dir == 0 && atom[j].dir == 1){
                        int time = abs(atom[i].y - atom[j].y);
                        pq.push(make_pair(time,make_pair(i,j)));
                    }
                }else if (atom[i].y == atom[j].y){
                    if(atom[i].x > atom[j].x && atom[i].dir ==2 && atom[j].dir == 3){
                        int time = abs(atom[i].x - atom[j].x);
                        pq.push(make_pair(time,make_pair(i,j)));
                    }else if(atom[i].x < atom[j].x && atom[i].dir ==3 && atom[j].dir == 2){
                        int time = abs(atom[i].x - atom[j].x);
                        pq.push(make_pair(time,make_pair(i,j)));
                    }
                }else{
                    int dx = abs(atom[i].x - atom[j].x);
                    int dy = abs(atom[i].y - atom[j].y);
                    if(dx != dy) continue;

                    int idir = atom[i].dir;
                    int jdir = atom[j].dir;

                    int nextix = atom[i].x + dirX[idir]*dx;
                    int nextiy = atom[i].y + dirY[idir]*dy;
                    int nextjx = atom[j].x + dirX[jdir]*dx;
                    int nextjy = atom[j].y + dirY[jdir]*dy;

                    if(nextix == nextjx && nextiy == nextjy){
                        pq.push(make_pair(2*dx  ,make_pair(i,j)));
                    }
                }
            }
        }

        int before = -1;
        int cur  = 0;
        while(!pq.empty()){
            before = cur;
            cur = pq.top().first;
            int i = pq.top().second.first;
            int j = pq.top().second.second;
            pq.pop();
            
            if(!exploded[i] && !exploded[j]){
                exploded[i] = cur;
                exploded[j] = cur;
                totalE += atom[i].energy;
                totalE += atom[j].energy;
            }else if(!exploded[i]){
                if(exploded[j] == cur){
                    exploded[i] = cur;
                    totalE += atom[i].energy;
                }
            }else if(!exploded[j]){
                if(exploded[i] == cur){
                    exploded[j] = cur;
                    totalE += atom[j].energy;
                }
            }
        }
        cout<<"#"<<test_case<<' '<<totalE<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}