#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <regex>
#include <atlstr.h>
#include <fstream>

using namespace std;

int GainAdminPrivileges(CString strApp) {
    SHELLEXECUTEINFO execinfo;
    memset(&execinfo, 0, sizeof(execinfo));
    execinfo.lpFile = strApp;
    execinfo.cbSize = sizeof(execinfo);
    execinfo.lpVerb = _T("runas");
    execinfo.fMask = SEE_MASK_NO_CONSOLE;
    execinfo.nShow = SW_SHOWDEFAULT;

    ShellExecuteEx(&execinfo);
    return 0;
}

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

int getMAC(string& str, string my_gateway) {
    execCmd("arp -a", str);
    string pattern_str = my_gateway + "\\s*(.+)\\s*[静|动]";
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

bool compareMACAddress(string str) {
    cout << "Comparing..." << endl;
    string filename = "Addresses.txt";
    ifstream fin(filename);
    string strline;
    bool verify = false;
    while (getline(fin, strline))
    {
        
        cout << "文件读取" << strline << strline.size() << endl;
        cout << "实际MAC地址" << str << str.size() <<endl;
        if (strline == str) {
            verify = true;
            cout << "存在于清单中" << endl;
            break;
        }
    }
    fin.close();
    return verify;
}

void trim(string& s)
{
    int index = 0;
    if (!s.empty())
    {
        while ((index = s.find(' ', index)) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}