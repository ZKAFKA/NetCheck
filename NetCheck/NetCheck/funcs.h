#include <stdio.h>
#include<iostream>
#include<Windows.h>
#include<string>
#include <regex>

using namespace std;

int execCmd(const char* cmd, string& result) {
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) {
        printf_s("popen error");
        return -1;
    }
    size_t ret = 0;
    char buf[200] = { 0 };
    while ((ret = fread(buf, sizeof(char), 199, pipe)) == 199) {
        result.append(buf);
    }
    if (ferror(pipe) != 0) {
        printf_s("read pipe error");
        return -1;
    }
    if (feof(pipe) != 0) {
        printf_s("exec cmd:%s success", cmd);
        result.append(buf, ret);
    }
    return 0;
}

int getIP(string& result) {
    regex pattern("IPv4 µÿ÷∑[\\s|. ]*: (.*)\\s");
    smatch matches;
    cout << "∆•≈‰°£°£°£" << endl;

    if (regex_search(result, matches, pattern)) {
        cout << "Found match: " << matches[1].str() << std::endl;
    }
    else {
        cout << "No match found." << std::endl;
    }
    return 0;
}