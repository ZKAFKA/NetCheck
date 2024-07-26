#include"funcs.h"

using namespace std;

int main() {
    string result;
    // ²éÑ¯±¾»úIP
    execCmd("ipconfig", result);
    getIP(result);
    //execCmd("arp -a", result);

}
