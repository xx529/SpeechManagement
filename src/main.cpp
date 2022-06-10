#include <iostream>
#include <ctime>
#include "../h/speechManager.h"

using namespace std;


int main()
{
    srand((unsigned int)time(NULL));
    SpeechManager sm;
    int choice = 0;
    
    for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
    {
        cout << "选手：" << it->first << "  "
             << "姓名：" << it->second.m_name << "  "
             << "成绩1：" << it->second.m_score[0] << "  "
             << "成绩2：" << it->second.m_score[1] << "  "
             << endl;
    }
    
    while (true)
    {
        sm.show_Meun();
        cout << "请输入你的选择: ";
        cin >> choice;
        cout << endl;
        
        switch (choice)
        {
            case 1:
                sm.startSpeech();
                break;
            
            case 2:
                sm.showRecord();
                break;
            
            case 3:
                sm.clearRecord();
                break;

            case 0:
                sm.exitSystem();

            default:
                system("cls");
                break;      
        }
        
    }
    
    return 0;
}