#include <stdio.h>
#include<iostream>
#include<Windows.h>
#include<string>
#include <regex>

using namespace std;

int execCmd(const char* cmd, string& str) {
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) {
        printf_s("popen error");
        return -1;
    }
    size_t ret = 0;
    char buf[200] = { 0 };
    while ((ret = fread(buf, sizeof(char), 199, pipe)) == 199) {
        str.append(buf);
    }
    if (ferror(pipe) != 0) {
        printf_s("read pipe error");
        return -1;
    }
    if (feof(pipe) != 0) {
        printf_s("exec cmd:%s success", cmd);
        str.append(buf, ret);
    }
    return 0;
}

int getIP(string& str) {
    execCmd("ipconfig", str);
    regex pattern("IPv4 地址[\\s|. ]*: (.*)\\s");
    smatch matches;
    if (regex_search(str, matches, pattern)) {
        cout << "Found match: " << matches[1].str() << std::endl;
        str = matches[1].str();
    }
    else {
        cout << "No match found." << endl;
    }
    return 0;
}

int getGateway(string& str) {
    execCmd("ipconfig", str);
    regex pattern("默认网关[\\s|. ]*: (.*)\\s");
    smatch matches;
    if (regex_search(str, matches, pattern)) {
        cout << "Found match: " << matches[1].str() << endl;
        str = matches[1].str();
    }
    else {
        cout << "No match found." << endl;
    }
    return 0;
}

int getMAC(string& str, string& my_gateway) {
    execCmd("arp -a", str);
    string pattern_str = my_gateway + "\\s*(.+)\\s*[静|动]";
    cout << pattern_str << endl;
    regex pattern(pattern_str);
    smatch matches;
    if (regex_search(str, matches, pattern)) {
        cout << "Found match: " << matches[1].str() << endl;
        str = matches[1].str();
    } 
    else {
        cout << "No match found." << endl;
    }
    return 0;
}

int getLegalGateway(string& str) {
    regex pattern("\\d+.\\d+.\\d+.");
    smatch matches;
    if (regex_search(str, matches, pattern)) {
        str = matches.str().append("254");
    }
    else {
        cout << "No match found." << endl;
    }
    return 0;
}

int compareMACaddress(string& str) {
    

}