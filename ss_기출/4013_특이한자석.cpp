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
#include <cstring>
#include <cmath>

using namespace std;


int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int K;
        cin>>K;
        vector<int> magnet[4];
        int magnetIndex[4]= {160,160,160,160};
        for(int i = 0; i < 4; i++){
            for(int  j = 0; j < 8 ; j ++){
                int pole;
                cin>>pole;
                magnet[i].push_back(pole);
            }
        }
        for(int i = 0; i < K ; i++){
            int magnetNum,rotate;
            cin>>magnetNum>>rotate;
            //회전 정보
            bool isRotate[3];
            isRotate[0] = magnet[0][(magnetIndex[0] +2)%8] != magnet[1][(magnetIndex[1] +6)%8];
            isRotate[1] = magnet[1][(magnetIndex[1] +2)%8] != magnet[2][(magnetIndex[2] +6)%8];
            isRotate[2] = magnet[2][(magnetIndex[2] +2)%8] != magnet[3][(magnetIndex[3] +6)%8];

            magnetIndex[magnetNum - 1] -= rotate;
            //rotate left magnet?
            int leftmag = magnetNum - 2;
            int leftpoint = magnetNum - 2;
            int leftcw = -rotate;
            while(leftmag >= 0 && leftpoint>=0){
                if(!isRotate[leftpoint]) break;
                magnetIndex[leftmag] -= leftcw;
                leftmag--;
                leftpoint--;
                leftcw = -leftcw;
            }
            
            //rotate right magnet?
            int rightmag = magnetNum;
            int rightpoint = magnetNum - 1;
            int rightcw = -rotate;
            while(rightmag < 4 && rightpoint < 4){
                if(!isRotate[rightpoint]) break;
                magnetIndex[rightmag] -= rightcw;
                rightmag++;
                rightpoint++;
                rightcw = -rightcw;
            }
            //cout<<i<<" "<<magnetIndex[0]<<" "<<magnetIndex[1]<<" "<<magnetIndex[2]<<" "<<magnetIndex[3]<<endl;
        }
        int score = 0;
        for(int i =0 ; i <4; i++){
            if(magnet[i][magnetIndex[i]%8] == 1) score += pow(2,i);
        }
        cout<<"#"<<test_case<<" "<<score<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}