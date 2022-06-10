#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include "../h/speaker.h"

using namespace std;

class SpeechManager
{
public:
    
    vector<int> v1;
    
    vector<int> v2;
    
    vector<int> v3;
    
    bool fileIsEmpty;
    
    map<int, vector<string>> m_Record;
    
    map<int, Speaker> m_Speaker;
    
    int m_idx;
    
    SpeechManager();
    
    void show_Meun();
    
    void exitSystem();
    
    ~SpeechManager();
    
    void init_speech();
    
    void createSpeaker();
    
    void startSpeech();
    
    void speechDraw();
    
    void speechContest();
    
    void showScore();
    
    void loadRecord();
    
    void saveRecord();
    
    void showRecord();
    
    void clearRecord();
    
};