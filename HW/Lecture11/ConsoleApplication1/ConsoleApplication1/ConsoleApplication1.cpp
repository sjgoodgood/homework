#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int count = 0;

    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    int delay_time_ms = 0;

    while (count < 10)
    {
        //슬립
        this_thread::sleep_for(chrono::milliseconds(1000 + delay_time_ms));
        //시작시간과 끝시간
        prev_end = end;
        end = chrono::steady_clock::now();
        //시간차 구하기
        chrono::steady_clock::duration diff = end - prev_end;
        delay_time_ms = 1000 - chrono::duration_cast<chrono::milliseconds>(diff).count();
        //출력
        count++;
        cout << count << "   dur:" << delay_time_ms << endl;
    }
}

/*int main()
{
    int count = 0;
    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    int delay_time_ms = 0;

    while (count < 10)
    {   
        //this_thread::sleep_for(chrono::seconds(1));
        // 시작 시간과 끝 시간을 기록합니다.
        this_thread::sleep_for(chrono::milliseconds(1000));
        prev_end = end;
        end = chrono::steady_clock::now();

        // 시간 차를 구합니다.
        chrono::steady_clock::duration diff = end - prev_end;
        delay_time_ms =chrono::duration_cast<chrono::milliseconds>(diff).count();

        // 출력합니다.
        count++;
        cout << count <<"   dur:" << delay_time_ms << endl;

        // 1초 대기를 합니다.
    }

    return 0;
}
*/

/*
int main()
{
    int count = 0;

    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    int delay_time_ms = 0;

    this_thread::sleep_for(chrono::milliseconds(1));

    prev_end = end;
    end = chrono::steady_clock::now();
    
    while (count < 10)
    {
        //시작시간과 끝시간
        prev_end = end;
        end = chrono::steady_clock::now();

        count++;
        //시간차 구하기
        ///chrono::steady_clock::duration diff = end - prev_end;
    
        delay_time_ms = chrono::duration_cast<chrono::milliseconds>(end - prev_end).count()-1000;

        //출력
        cout << count <<" "<< delay_time_ms << endl;

        //슬립
        this_thread::sleep_for(chrono::milliseconds(delay_time_ms));

    }
}
*/























