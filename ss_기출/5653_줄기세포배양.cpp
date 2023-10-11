/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include <vector>
#include <queue>
#include <list>
#include <tuple>

using namespace std;

int dirX[4] = {1,-1,0,0};
int dirY[4] = {0,0,1,-1};
const int initX = 400;
const int initY = 400;

class cell{
    public:
    int lifeVal;
    int curVal;
    bool occupied;

    cell(){
        lifeVal = 0;
        curVal = 0;
        occupied = false;
    }
};

class compare{
    public:
    bool operator()(const tuple<int,int,int>& a, const tuple<int,int,int>&b){
        return get<2>(a) < get<2>(b);
    }
};

class infinitePatri{
    public:
    cell patriGrid[800][800];
    list<tuple<int,int>> aliveCells;
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,compare> reproduceCells;
    void init(){
        for(int i = 0; i<800;i++){
            for(int j=0;j<800;j++){
                patriGrid[i][j].occupied = false;
                patriGrid[i][j].lifeVal = 0;
                patriGrid[i][j].curVal = 0;
                
            }
        }
        aliveCells.clear();
        while(!reproduceCells.empty()){
            reproduceCells.pop();
        }
    }
    void act(){
        priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,compare> temp;
        //reproduce
        for(list<tuple<int,int>>::iterator it = aliveCells.begin(); it != aliveCells.end() ;it++){
            int i,j;
            i = get<0>(*it) ;
            j = get<1>(*it) ;

            if(patriGrid[i ][j].curVal == patriGrid[i ][j].lifeVal ){
                temp.push(make_tuple(i,j,patriGrid[i ][j].lifeVal));
            }
        }
        reproduceCells = temp;
    }

    void update(){
       
        //life decrase and kill
        for(list<tuple<int,int>>::iterator it = aliveCells.begin(); it != aliveCells.end() ;){
            
            int i,j;
            i = get<0>(*it) ;
            j = get<1>(*it) ;

            patriGrid[i][j].curVal--;
            if(patriGrid[i][j].curVal == 0){
                it=aliveCells.erase(it);
            }else{
                it++;
            }
        }
        
        //reproduce
        while(!reproduceCells.empty()){
            tuple<int,int,int> temp = reproduceCells.top();
            reproduceCells.pop();
            int i = get<0>(temp);
            int j = get<1>(temp);
            int life = get<2>(temp);
            for(int dir = 0; dir <4; dir++){
                if(!patriGrid[i+dirX[dir]][j+dirY[dir]].occupied){
                    patriGrid[i+dirX[dir]][j+dirY[dir]].occupied = true;
                    patriGrid[i+dirX[dir]][j+dirY[dir]].lifeVal = life;
                    patriGrid[i+dirX[dir]][j+dirY[dir]].curVal = life*2;
                    
                    aliveCells.push_back(make_tuple(i+dirX[dir],j+dirY[dir]));
                }
            }
        }

        /*
        for(list<tuple<int,int>>::iterator it = aliveCells.begin(); it != aliveCells.end() ;it++){
            int i,j;
            i = get<0>(*it);
            j = get<1>(*it);
            cout<<i<<j<<patriGrid[i][j].curVal<<endl;
        }
        cout<<"====="<<endl;
        */
    }
};

infinitePatri infPatri;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int n,m,k;
        infPatri.init();
		cin>>n>>m>>k;
        int life;
        for(int i =0 ; i<n ; i++){
            for(int j = 0; j < m;j++){
                cin>>life;
                if(life == 0)continue;
                infPatri.patriGrid[initX + i][initY+j].occupied = true;
                infPatri.patriGrid[initX + i][initY+j].lifeVal = life;
                infPatri.patriGrid[initX + i][initY+j].curVal = life*2;
                infPatri.aliveCells.push_back(make_tuple(initX +i,initY + j));
            }
        }

        for(int i = 0; i < k;i++){
            infPatri.act();
            infPatri.update();
        }

        cout<<"#"<<test_case<<" "<<infPatri.aliveCells.size()<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}