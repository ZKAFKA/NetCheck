#include"funcs.h"

using namespace std;

int main() {
    string result;
    // ��ѯ����IP
    execCmd("ipconfig", result);
    getIP(result);
    //execCmd("arp -a", result);

}
