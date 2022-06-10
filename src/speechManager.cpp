#include <iostream>
#include "../h/speechManager.h"

SpeechManager::SpeechManager()
{
    this->init_speech();
    cout << "初始化成功 SpeechManager" << endl;
    
    this->createSpeaker();
    cout << "初始化成功 Speaker " << this->v1.size() << endl;
    
    this->loadRecord();
    cout << "加载/初始化记录成功" << endl;
};

SpeechManager::~SpeechManager()
{
    
}

void SpeechManager::show_Meun()
{
    cout << endl;
    cout << "************************" << endl;
    cout << "***** 欢迎参加比赛 *****" << endl;
    cout << "**** 1.开始演讲比赛 ****" << endl;
    cout << "**** 2.查看往届记录 ****" << endl;
    cout << "**** 3.清空比赛记录 ****" << endl;
    cout << "**** 0.退出比赛程序 ****" << endl;
    cout << endl;
}

void SpeechManager::exitSystem()
{
    cout << "*** 欢迎再此使用 ***" << endl;
    exit(0);
}

void SpeechManager::init_speech()
{
    this->v1.clear();
    this->v2.clear();
    this->v3.clear();
    this->m_Speaker.clear();
    this->m_idx = 1;
    this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    
    for (int i=0; i<nameSeed.size(); i++)
    {
        string name="选手";
        name += nameSeed[i];
        
        Speaker sp;
        sp.m_name = name;
        
        sp.m_score[0] = 0.0;
        sp.m_score[1] = 0.0;
        
        this->v1.push_back(i+10001);
        this->m_Speaker.insert(make_pair(i+10001, sp));
        
    }
}

void SpeechManager::startSpeech()
{
    for (int i=0; i<2; i++)
    {
        this->speechDraw();
        this->speechContest();
        this->showScore();
        this->m_idx ++;
    }
    
    this->saveRecord();
    this->init_speech();
    this->createSpeaker();
    this->loadRecord();
}

void SpeechManager::speechDraw()
{
    cout << "第 < " << this->m_idx << " > 轮抽签" << endl;
    cout << "----------------------" << endl;
    cout << "抽签后顺序：" ;
    
    if (m_idx == 1)
    {
        random_shuffle(this->v1.begin(), this->v1.end());
        for (vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
        {
            cout << *it << " " ;
        }
        cout << endl;
    }
    
    else
    {
        random_shuffle(this->v2.begin(), this->v2.end());
        for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
        {
            cout << *it << " " ;
        }
        cout << endl;
    }
    
    cout << "----------------------" << endl;
}

void SpeechManager::speechContest()
{
    cout << "第 < " << this->m_idx << " > 轮比赛开始" << endl;
    cout << endl;
    
    vector<int> v_cur;
    multimap<double, int, greater<double>> groupScore;
    int num = 0;
    
    if (this->m_idx == 1) {v_cur = this->v1;}
    else {v_cur = this->v2;}
    
    for (vector<int>::iterator it = v_cur.begin(); it != v_cur.end(); it++)
    {
        num ++;
        deque<double> q;
        
        for (int i=0; i<10; i++)
        {
            double score = (rand() % 401 + 600)/10.f;
            q.push_back(score);
            
        }
        
        sort(q.begin(), q.end(), greater<double>());
        
        q.pop_front();
        q.pop_back();
        
        double sum = accumulate(q.begin(), q.end(), 0.0f);
        double avg = sum / (double)q.size();
        
        this->m_Speaker[*it].m_score[this->m_idx-1] = avg;
        
        groupScore.insert(make_pair(avg, *it));
        
        if (num % 6 == 0)
        {
            cout << "第 " << num/6 << " 小组名次如下：" << endl;
            
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                Speaker cur_speaker = this->m_Speaker[(*it).second];
                cout << "姓名：" << cur_speaker.m_name << " " << "编号：" << (*it).second << " " << "平均分：" << cur_speaker.m_score[this->m_idx-1] << endl;
            }
            
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->m_idx == 1)
                {
                    this->v2.push_back((*it).second);
                }
                else
                {
                    this->v3.push_back((*it).second);
                }
            }
            
            cout << endl;
            groupScore.clear();
        }
    }
    
}

void SpeechManager::showScore()
{
    cout << "第 < " << this->m_idx << " > 轮比赛结束，晋级名单：" << endl;
    vector<int> v;
    
    if (this->m_idx == 1)
    {
        v = this->v2;
    }
    else
    {
        v = this->v3;
    }
    
    for (vector<int>::iterator it=v.begin(); it!=v.end(); it++)
    {
        cout << this->m_Speaker[*it].m_name << "：" << this->m_Speaker[*it].m_score[this->m_idx-1] << endl;
    }
    
}

void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::in | ios::app);
    
    for (vector<int>::iterator it=v3.begin(); it != v3.end(); it++)
    {
        ofs << *it << "," << m_Speaker[*it].m_score[1] << ",";
    }
    ofs << endl;
    ofs.close();
    
    this->fileIsEmpty = false;

    
    cout << "比赛结果记录成功" << endl;
}

void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv", ios::in);
    
    if (!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }
    
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }
    
    this->fileIsEmpty = false;
    
    ifs.putback(ch);
    
    string data;
    int idx = 0;
    while (ifs >> data)
    {
        vector<string> v;
        int pos = -1;
        int start = 0;
        
        while (true)
        {
            pos = data.find(",", start);
            if (pos == -1)
            {
                break;
            }
            
            string tmp = data.substr(start, pos - start);
            v.push_back(tmp);
            start = pos + 1;
        }
        
        this->m_Record.insert(make_pair(idx, v));
        idx ++;
        
    }
    
    ifs.close();
  
}

void SpeechManager::showRecord()
{
    if (this->fileIsEmpty)
    {
        cout << "文件记录不存在！" << endl;
        return ;
    }
    for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
    {
        cout << "第 " <<(*it).first + 1 << " 届比赛冠军：" << (*it).second[0] << "，分数：" << (*it).second[1] << endl;
    }
}

void SpeechManager::clearRecord()
{
    cout << "确认清空" << endl;     
    cout << "1 yes " << endl;
    cout << "2 no " << endl;
    
    int select = 0;
    cin >> select;
        
    if (select == 1)
    {
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();
        
        this->init_speech();
        this->createSpeaker();
        this->loadRecord();
        
        cout << "清理成功" << endl;
        
    }
}