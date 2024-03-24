#include <iostream>

using namespace std;

enum ForeColour
{
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

int main()
{
    int num = 0;
    int rest = 1;
    bool okay = true;
    int condition = 32;
    cout << "\x1b[000m" << "화면에 그림을 그리는 프로그램입니다." << endl;
    cout << "학번 : 202327048" << endl;
    cout << "이름 : 본인이름" << endl;
    cout << "화면에 그릴 물체코드를 입력하세요 :" << endl;
    cin >> num;



    while (num != 64)
    {
        while (true)
        {
            if (condition == 32)
            {
                rest = num / 32;
                if (num % 32 == 0 || rest == 32)
                {
                    cout << "\x1b[035m" << "ㅁ" << endl;
                    if (num % 32 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                  
                }
                condition = 16;
            }

            else if (condition == 16)
            {
                rest = num / 16;
                if (num % 16 == 0 || rest == 16)
                {
                    cout << "\x1b[036m" << "ㅁ" << endl;
                    if (num % 16 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
               
                }
                condition = 8;
            }

            else if (condition == 8)
            {
                rest = num / 8;
                if (num % 8 == 0 || rest == 8)
                {
                    cout << "\x1b[033m" << "ㅁ" << endl;
                    if (num % 8 == 0)
                    {   
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 4;
            }

            else if (condition == 4)
            {
                rest = num / 4;
                if (num % 4 == 0 || rest == 4)
                {
                    cout << "\x1b[032m" << "ㅁ" << endl;
                    if (num % 4 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 2;
            }

            else if (condition == 2)
            {
                rest = num / 2;
                if (num % 2 == 0 || rest == 2)
                {
                    cout << "\x1b[031m" << "ㅁ" << endl;
                    if (num % 2 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 1;
            }

            else if (condition == 1)
            {
                rest = num / 1;
                if (num % 1 == 0 || rest == 1)
                {
                    cout << "\x1b[037m" << "ㅁ" << endl;
                    if (num % 1 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 0;
            }
        }

        cout << "화면에 그릴 물체코드를 입력하세요 :" << endl;
        cin >> num;
        condition = 32;
        okay = true;
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



