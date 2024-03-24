#include <iostream>

using namespace std;


int main()
{
    int num = 0;
    int r = 1;
    bool k = true;
    int cont = 32;
    cout << "\x1b[000m" << "화면에 그림을 그리는 프로그램입니다." << endl;
    cout << "학번 : 202327048" << endl;
    cout << "이름 : 최수정" << endl;
    cout << "화면에 그릴 물체코드를 입력하세요 :" << endl;
    cin >> num;

    while (num != 64)
    {
        while (k)
        {
            if (cont == 32)
            {
                r = num / 32;
                if (num % 32 == 0 || r >= 1)
                {
                    r = 0;
                 
                    cout << "\x1b[035m " << "#########\n";
                    cout << "\x1b[035m " << "#       #\n";
                    cout << "\x1b[035m " << "#########\n";
                    num -= 32;
                    if (num % 32 == 0)
                    {
                        cont = 0;
                        k = false;
                        break;
                    }
                }
                cont = 16;
            }

            else if (cont == 16)
            {
                r = num / 16;
                if (num % 16 == 0 || r >= 1)
                {
                    r = 0;
                   
                    cout << "\x1b[036m " << "#########\n";
                    cout << "\x1b[036m " << "#       #\n";
                    cout << "\x1b[036m " << "#########\n";
                    num -= 16;
                    if (num % 16 == 0)
                    {
                        cont = 0;
                        k = false;
                        break;
                    }
                }
                cont = 8;
            }

            else if (cont == 8)
            {
                r = num / 8;
                if (num % 8 == 0 || r >= 1)
                {
                    r = 0;
                    
                    cout << "\x1b[033m " << "#########\n";
                    cout << "\x1b[033m " << "#       #\n";
                    cout << "\x1b[033m " << "#########\n";
                    num -= 8;
                    if (num % 8 == 0)
                    {
                        cont = 0;
                        k = false;
                        break;
                    }
                }
                cont = 4;
            }

            else if (cont == 4)
            {
                r = num / 4;
                if (num % 4 == 0 || r >= 1)
                {
                    r = 0;
                    
                    cout << "\x1b[032m " << "#########\n";
                    cout << "\x1b[032m " << "#       #\n";
                    cout << "\x1b[032m " << "#########\n";
                    num -= 4;
                    if (num % 4 == 0)
                    {
                        cont = 0;
                        k = false;
                        break;
                    }
                }
                cont = 2;
            }

            else if (cont == 2)
            {
                r = num / 2;
                if (num % 2 == 0 || r >= 1)
                {
                    r = 0;
                   
                    cout << "\x1b[031m " << "#########\n";
                    cout << "\x1b[031m " << "#       #\n";
                    cout << "\x1b[031m " << "#########\n";
                    num -= 2;
                    if (num % 2 == 0)
                    {
                        cont = 0;
                        k = false;
                        break;
                    }
                }
                cont = 1;
            }

            else if (cont == 1)
            {
                r = num / 1;
                if (num % 1 == 0 || r >= 1)
                {
                    r = 0;
                    
                    cout << "\x1b[037m " << "#########\n";
                    cout << "\x1b[037m " << "#       #\n";
                    cout << "\x1b[037m " << "#########\n";
                    num -= 1;
                    if (num % 1 == 0)
                    {
                        cont = 0;
                        k = false;
                        break;
                    }
                }
                cont = 0;
            }
        }

        cout << "화면에 그릴 물체코드를 입력하세요 :" << endl;
        cin >> num;
        cont = 32;
        k = true;
    }

}

/*
* 흰색 블록을 그리는 키코드 : 1 (1)
* 빨강색 블록을 그리는 키코드 : 2 (10)
* 녹색 블록을 그리는 키코드 : 4 (100)
* 노란색 블록을 그리는 키코드 : 8 (1000)
* 청록색 블록을 그리는 키코드 : 16 (10000)
* 마젠타색 블록을 그리는 키코드 : 32 (100000)
* 프로그램 종료 : 64 (1000000)
*
* 프로그램을 시작하면 아래와 같이 쓰시오
*
*
* 화면에 그림을 그리는 프로그램입니다.
* 학번 : 349218347(본인학번)
* 이름 : 본인이름
*
* 화면에 그릴 물체코드를 입력하세요 :
* (반복)
*/
