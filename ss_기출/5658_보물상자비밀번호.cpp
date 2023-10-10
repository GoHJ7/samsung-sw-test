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
#include <queue>
#include <set>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;
int charToNum(char c, int power){
    int ret = -1;
    switch(c){
        case '0':
            ret = 0 * pow(16,power);
            break;
        case '1':
            ret = 1 * pow(16,power);
            break;
        case '2':
            ret = 2 * pow(16,power);
            break;
        case '3':
            ret = 3 * pow(16,power);
            break;
        case '4':
            ret = 4 * pow(16,power);
            break;
        case '5':
            ret = 5 * pow(16,power);
            break;
        case '6':
            ret = 6 * pow(16,power);
            break;
        case '7':
            ret = 7 * pow(16,power);
            break;
        case '8':
            ret = 8 * pow(16,power);
            break;
        case '9':
            ret = 9 * pow(16,power);
            break;
        case 'A':
            ret = 10 * pow(16,power);
            break;
        case 'B':
            ret = 11 * pow(16,power);
            break;
        case 'C':
            ret = 12 * pow(16,power);
            break;
        case 'D':
            ret = 13 * pow(16,power);
            break;
        case 'E':
            ret = 14 * pow(16,power);
            break;
        case 'F':
            ret = 15 * pow(16,power);
            break;
        default:
            cout<<"something wrong with the range\n";
            break;
    }
    return ret;
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
	freopen("input.txt", "r", stdin);
    freopen("output.txt","w",stdout);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int n,k;
        cin>>n>>k;
        set<int> s;
        priority_queue<int> pq;
        char ch[n];
        for(int i= 0; i<n ; i++){
            cin>>ch[i];
        }

        //move index 0 to n-1
        for(int startIndex = 0 ; startIndex < n; startIndex++){
            int arr[4];
            memset(arr,0,sizeof(arr));
            for(int i = 0 ; i < n/4; i++){
                for(int j=0; j<4; j++){
                    //cout<<charToNum(ch[(n-startIndex + i + (n/4)*j)%n],n/4-i-1)<< " ";
                    arr[j-1] += charToNum(ch[(n-startIndex + i + (n/4)*j)%n],n/4-i-1);
                }
            }
            
            s.insert(arr[0]);
            s.insert(arr[1]);
            s.insert(arr[2]);
            s.insert(arr[3]);
        }

        for(set<int>::iterator it = s.begin(); it != s.end(); it++){
            pq.push(*it);
        }

        for(int i= 0; i< k-1; i++){
            pq.pop();
        }
        cout<<"#"<<test_case<<" "<<pq.top()<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}