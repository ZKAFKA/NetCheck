#include"funcs.h"

using namespace std;

int main() {
    // Get Administrator's Authority
    //WCHAR path[MAX_PATH] = { 0 };
    //GetModuleFileName(NULL, path, MAX_PATH);
    //GainAdminPrivileges(path);

    while (true) {
        // Get IP
        string my_ip;
        getIP(my_ip);
        cout << "My IP:" << my_ip << endl;

        // Get Gateway
        string my_gateway;
        getGateway(my_gateway);
        cout << "Current Gateway:" << my_gateway << endl;

        // Compute Legal Gateway
        string legal_gateway = my_ip;
        getLegalGateway(legal_gateway);
        cout << "Legal Gateway:" << legal_gateway << endl;

        // Compare Gateway
        if (my_gateway == legal_gateway) {
            // Compare MAC address
            string mac_address;
            getMAC(mac_address, my_gateway);
            trim(mac_address);
            bool verify = compareMACAddress(mac_address);
            if (verify == false) {
                // Block the Network
                BlockNet();
            }
        }
        else {
            // Block the Network
            BlockNet();
        }

        Sleep(10000);
    }
    
}
