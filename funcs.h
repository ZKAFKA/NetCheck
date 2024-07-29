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
        str.append(buf, ret);
    }
    return 0;
}

int getIP(string& str) {
    execCmd("ipconfig", str);
    regex pattern("以太网[\\S|\\s]*IPv4 地址[\\s|. ]*: (.*)\\s");
    smatch matches;
    if (regex_search(str, matches, pattern)) {
        str = matches[1].str();
    }
    else {
        cout << "No match found." << endl;
    }
    return 0;
}

int getGateway(string& str) {
    execCmd("ipconfig", str);
    regex pattern("以太网[\\S|\\s]*默认网关[\\s|. ]*: (.*)\\s");
    smatch matches;
    if (regex_search(str, matches, pattern)) {
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
        str = matches[1].str();
    } 
    else {
        // assign null value when not find the MAC address
        str = "xx-xx-xx-xx-xx-xx";
    }
    return 0;
}

int getLegalGateway(string& str) {
    regex pattern("\\d+.\\d+.\\d+.");
    smatch matches;
    regex_search(str, matches, pattern);
    str = matches.str().append("254");
    return 0;
}

bool compareMACAddress(string str) {
    string filename = "Addresses.txt";
    ifstream fin(filename);
    string strline;
    bool verify = false;
    while (getline(fin, strline))
    {
        cout << "Comparing MAC Address" << strline.c_str()<< ":" << str.c_str() << endl;
        if (strncmp(strline.c_str(), str.c_str(), 17)==0) {
            verify = true;
            cout << "Verify！" << endl;
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

int BlockNet() {
    // Block the Network
    string null_str;
    execCmd("netsh interface set interface 以太网 disabled", null_str);
    MessageBox(NULL, (LPCTSTR)TEXT("您的网络连接已被禁用，请联系科技运维人员解除"), (LPCTSTR)TEXT("提示"), MB_OK);
    return 0;
}