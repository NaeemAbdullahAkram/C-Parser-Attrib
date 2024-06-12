#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
#include <string>
using namespace std;

string attributeParrser(string q, string txt, vector<string> path){
    vector<string> tags, sub_tag;
    string q2 = q;
    smatch m_tag1;
    regex reg1("([a-z]+\\d*)\\.");
    while(regex_search(q, m_tag1, reg1)){
        //cout << m_tag1.str(1) << endl;
        tags.push_back(m_tag1.str(1));
        q = m_tag1.suffix();
    }
    q = q2;
    smatch m_tag2;
    regex reg2("([a-z]+\\d*)~[a-zA-Z\\d_]+\\d*");
    if(regex_search(q, m_tag2, reg2)){
        //cout << m_tag2.str(1) << endl;
        tags.push_back(m_tag2.str(1));
    }
    smatch m_tag3;
    regex reg3("[a-z]+\\d*~([a-zA-Z\\d_]+\\d*)");
    if(regex_search(q, m_tag3, reg3)){
        //cout<< "~: " << m_tag3.str(1) << endl;
        sub_tag.push_back(m_tag3.str(1));
    }
    //else cout << "error regex" << endl;
    string s_t = txt;
    string query;
    for(auto i : tags){
        //cout << "I: " << i << endl; 
        smatch m_tag4;
        regex reg4("<"+i+".*>\\w*\\d*</"+i+">");
        regex_search(s_t, m_tag4, reg4);
        query.insert(query.size(), i);
        s_t = m_tag4.str();
        //cout << "s_t: " << s_t << endl;
    }
    bool match = false;
    for(auto a : path){
        if(a==query) match = true;
    }
    //cout << "match: " << match << endl;
    smatch m_tag5;
    regex reg5("<"+tags.back()+"[\\s\\w\"=\\d\\.]* "+sub_tag.back()+" = \"([\\w\\d%!\\.$]*)\"");
    regex_search(s_t, m_tag5, reg5);
    s_t = m_tag5.str(1);
    ////////////////////
    //cout << query << endl;
    if(s_t=="") return "Not Found!";
    if(match==false) return "Not Found!";
    else return s_t;
}

vector<string> tags(string txt){
    ///////////////////////////////////////////
    vector<string> confirm;
    string s_t = txt;
    smatch m_tag6;
    regex reg6("<([\\w\\d%!/]+)[\\s\\w\"=%\\.!$]*>");
    while(regex_search(s_t, m_tag6, reg6)){
        confirm.push_back(m_tag6.str(1));
        s_t = m_tag6.suffix();
    }
    s_t=txt;
    for(auto i : confirm){
        //cout << "I: " << i << endl;
    }
    //////////////
    vector<string> path;
    string p = "/";
    string add;
    for(auto i : confirm){
        int compare_value{i.compare(0, 1, p, 0, 1)};
        //cout << compare_value << endl;
        if(compare_value==0 && add.size()>=i.size()-1){
        add.erase(add.size()-(i.size()-1), i.size()-1);
        }
        else add.insert(add.size(), i);
        path.push_back(add);
    }
    return path;
    //////////////////////////////////////////
}

int main() {
    short N, Q;
    cin >> N >> Q;
    string txt;
    for(short i=0; i<=N; i++){
        string text;
        getline(cin, text);
        txt += text;
    }
    //cout << endl;
    
    for(short i=0; i<Q; i++){
        string q, q2;
        getline(cin, q); 
        cout << attributeParrser(q, txt, tags(txt)) << endl;
    }
    for(auto i : tags(txt)){
        //cout << i << endl;
    }
       
    cin.ignore();
    return 0;
}