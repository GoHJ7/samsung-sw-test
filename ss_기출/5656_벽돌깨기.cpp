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
#include <algorithm>
#include <utility>
#include <queue>
#include <cmath>

using namespace std;

int dirX[4] = {1,-1,0,0};
int dirY[4] = {0,0,1,-1};

int calRemain(int w, int h,vector<vector<int>> phaseBrick){
    int countBrick = 0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(phaseBrick[i][j] != 0) countBrick++;
        }
    }
    //cout<<"count brick "<<countBrick<<endl;
    return countBrick;
}

int breakBrick(vector<int> shootingPosV, int w, int h, vector<vector<int>> phaseBrick){

    for(int T = 0 ;T < shootingPosV.size();T++){
        queue<pair<int,int>> q;
        vector<pair<int,int>> brokenCor;
        int row = 0;

       

        for(int i= 0;i<h;i++){
            if(phaseBrick[i][shootingPosV[T]] != 0){
                row = i;
                break;
            }
        }
        if(phaseBrick[row][shootingPosV[T]] == 0) continue;

        //bfs breaking logic
        bool visited[h][w];
        for(int i=0;i<h;i++){
            for(int j = 0;j<w;j++){
                visited[i][j] = false;
            }
        }
        q.push(make_pair(row,shootingPosV[T]));

        while(!q.empty()){
            int r,c;
            r = q.front().first;
            c = q.front().second;
            brokenCor.push_back(q.front());
            q.pop();
            for(int i = 0; i <4 ;i++){
                for(int j =1 ; j<phaseBrick[r][c];j++){
                    if(r + j*dirY[i] >= 0 && c + j*dirX[i] >= 0
                    && r + j*dirY[i]<h && c + j*dirX[i] < w
                    && !visited[r + j*dirY[i]][c + j*dirX[i]]
                    && phaseBrick[r + j*dirY[i]][c + j*dirX[i]] != 0){
                        q.push(make_pair(r + j*dirY[i],c + j*dirX[i]));
                        visited[r + j*dirY[i]][c + j*dirX[i]] = true;
                    }
                }
            }    
        }

        //break brick, set brick to 0
        for(int i = 0; i<brokenCor.size();i++){
            int r,c;
            r = brokenCor[i].first;
            c = brokenCor[i].second;

            phaseBrick[r][c] = 0;
        }
        
        //fall bricks
        for(int i = 0; i<w; i++){
            int brickCount = 0;
            for(int j = h-1; j>=0 ; j--){
                if(phaseBrick[j][i] != 0){
                    if(brickCount ==0 ) continue;
                    if(j + brickCount >= h) cout<<"count wrong"<<endl;
                    if(phaseBrick[j+brickCount][i] != 0) cout<<"why not brick below zero"<<endl;
                    phaseBrick[j+brickCount][i] = phaseBrick[j][i];
                    phaseBrick[j][i] = 0;

                }
                else{
                    brickCount ++;
                }
            }
        }

    }
    /*
    for(int i =0 ; i<shootingPosV.size();i++){
            cout<<shootingPosV[i];
    }
    cout<<endl;
    
    for(int i= 0; i<h;i++){
        for(int j = 0; j<w; j++){
            cout<<phaseBrick[i][j];
        }
        cout<<endl;
    }
    */
    int remainBrick= calRemain(w,h,phaseBrick);
    return remainBrick;
}



int getMaxBrick(int n, int w, int h, vector<vector<int>> brick){
    //branch phase
    int maxBrick = w*h;
    for(int i= 0 ; i<pow(w,n);i++){
        vector<int> arr;
        int temp = i;
        for(int j =0 ;j<n;j++){
            arr.push_back(temp % w); 
            temp /= w;
        }
        
        int phaseMaxBrick = breakBrick(arr,w,h,brick);
        maxBrick=min(maxBrick,phaseMaxBrick);
        if(maxBrick==0) return maxBrick;
    }
    return maxBrick;
}

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
    //freopen("output.txt","w",stdout);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int n,w,h;
        cin>>n>>w>>h;
        vector<vector<int>> brick;
        for(int  i= 0; i<h;i++){
            vector<int> temp;
            for(int j = 0; j<w;j++){
                int t;
                cin>>t;
                temp.push_back(t);
            }
            brick.push_back(temp);
        }

         
        cout<<"#"<<test_case<<" "<<getMaxBrick(n,w,h,brick)<<"\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}