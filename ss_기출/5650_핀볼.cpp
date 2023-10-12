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
#include <utility>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>

using namespace std;

int board[100][100];
int maxScore;
void init(){
    for(int j =0 ; j <100; j++){
        for(int k = 0; k <100;k++){
            board[j][k] = 0;
        }
    }
    maxScore = 0;
}

void move(int dir, int i, int j,int n);
int next(int& curDir, int& curI, int& curJ ,int n);
int dirX[4] = {-1,0,1,0};
int dirY[4] = {0,1,0,-1};

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
	freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        int n;
		cin>>n;
        for(int i = 0; i<n;i++){
            for(int j = 0; j < n; j++){
                cin>>board[i][j];
            }
        }

        //핀볼 결과 저장
        for(int i = 0; i<n;i++){
            for(int j = 0; j < n; j++){
                //북동남서
                for(int dir = 0; dir <4; dir++){
                    if(board[i][j] != 0){
                        continue;
                    }else{
                        move(dir,i,j,n);
                    }
                }
            }
        }
        cout<<"#"<<test_case<<" "<<maxScore<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

void move(int dir, int i , int j,int n){
    int maxS = 0;
    bool start = true;
    int curDir = dir;
    int curI = i;
    int curJ = j;
    


    //북동남서
    //움직임 탐색
    while(true){
        if(curI < 0 || curI >= n || curJ <0 || curJ >= n){
            maxS += next(curDir,curI,curJ,n);
            start = false;
            continue;
        }
        //움직임 끝 블랙홀 또는 시작지점
        if((curI == i && curJ == j && !start)|| board[curI][curJ] == -1){
            //경로 저장된거 해제
            break;
        }
        maxS += next(curDir,curI,curJ,n);
        start = false;
    }


    maxScore = max(maxScore,maxS);
}



int next(int& curDir, int& curI, int& curJ,int n){
    //next는 track에 경로를 넣는다. 벽포함, 장애물 포함
    //점수를 낸 만큼을 반환한다.
    //다음 움직임을 curDir,I,J에 저장한다. 장애물을 만난 경우엔 장애물 이후의 좌표를 저장한다.
    //시작 좌표 지점
    int retScore = 0;
    //벽
    if(curI == 0 && curDir == 0){
        //북쪽 벽
        curI += dirX[curDir];
        curJ += dirY[curDir];
        curDir = 2;
        retScore +=1;
        return retScore;
    }else if(curI == n-1 && curDir ==2){
        //남쪽벽
        curI += dirX[curDir];
        curJ += dirY[curDir];
        curDir = 0;
        retScore +=1;
        return retScore;
    }else if(curJ == 0 && curDir == 3){
        //서쪽벽
        curI += dirX[curDir];
        curJ += dirY[curDir];
        curDir = 1;
        retScore +=1;
        retScore +=1;
        return retScore;
    }else if(curJ == n-1 && curDir == 1){
        //동쪽벽
        curI += dirX[curDir];
        curJ += dirY[curDir];
        curDir = 3;
        retScore +=1;
        return retScore;
    }

   

    //빈칸
    if(board[curI + dirX[curDir]][curJ + dirY[curDir]] == 0){
        //cout<<"빈칸"<<endl;
        curI += dirX[curDir];
        curJ += dirY[curDir];
        return 0;
    }
    //블록
    if(board[curI + dirX[curDir]][curJ + dirY[curDir]]>=1 && board[curI + dirX[curDir]][curJ + dirY[curDir]]<=5){
        switch(board[curI + dirX[curDir]][curJ + dirY[curDir]]){
            case 1:
            //북->남, 동->서, 남->동,서->북
            curI += dirX[curDir];
            curJ += dirY[curDir];
            if(curDir == 0){
                curDir = 2;
            }else if(curDir == 1){
                curDir = 3;
            }else if(curDir == 2){
                curDir = 1;
            }else{
                curDir = 0;
            }
            break;
            case 2:
            //북->동,동->서, 남->북,서->남
            curI += dirX[curDir];
            curJ += dirY[curDir];
            if(curDir == 0){
                curDir = 1;
            }else if(curDir == 1){
                curDir = 3;
            }else if(curDir == 2){
                curDir = 0;
            }else{
                curDir = 2;
            }
            break;
            case 3:
            //북->서,동->남, 남->북,서->동
            curI += dirX[curDir];
            curJ += dirY[curDir];
            if(curDir == 0){
                curDir = 3;
            }else if(curDir == 1){
                curDir = 2;
            }else if(curDir == 2){
                curDir = 0;
            }else{
                curDir = 1;
            }
            break;
            case 4:
            //북->남,동->북, 남->서,서->동
            curI += dirX[curDir];
            curJ += dirY[curDir];
            if(curDir == 0){
                curDir = 2;
            }else if(curDir == 1){
                curDir = 0;
            }else if(curDir == 2){
                curDir = 3;
            }else{
                curDir = 1;
            }
            break;
            case 5:
            //북->남,동->서, 남->북,서->동
            curI += dirX[curDir];
            curJ += dirY[curDir];
            if(curDir == 0){
                curDir = 2;
            }else if(curDir == 1){
                curDir = 3;
            }else if(curDir == 2){
                curDir = 0;
            }else{
                curDir = 1;
            }
            break;
            default:
            break;
        }
        retScore +=1;
        return retScore;
    }
    
    
    curI += dirX[curDir];
    curJ += dirY[curDir];
    //웜홀
    if(board[curI][curJ]>=6 &&board[curI][curJ]<=10 ){
        for(int x = 0; x<n;x++){
            for(int y =0; y<n; y++){
                if(board[curI][curJ] == board[x][y] && (curI != x || curJ != y)){
                    curI = x;
                    curJ = y;
                    return retScore;
                }
            }
        }
    }
    //hmmm
    if(board[curI][curJ] == -1) return retScore;
    cout<<"what is here?"<<endl;
    return retScore;
}
