#include"funcs.h"

using namespace std;

int main() {
    // Get IP
    string my_ip;
    getIP(my_ip);
    cout << my_ip << endl;

    // Get Gateway
    string my_gateway;
    getGateway(my_gateway);
    cout << my_gateway << endl;

    // Compute Legal Gateway
    string legal_gateway = my_ip;
    getLegalGateway(legal_gateway);
    cout << legal_gateway << endl;

    // Compare Gateway

    string mac_address;
    getMAC(mac_address, my_gateway);
    cout << mac_address << endl;
    compareMACAddress(mac_address);
    if (my_gateway == legal_gateway) {
        // Compare MAC address
        
        // 
    }
    else {
        // Block the Network
        execCmd("netsh interface set interface ��̫�� disabled", str);
    }


    // ��ȡ��ǰ
    //execCmd("arp -a", result);

}
