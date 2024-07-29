#include"funcs.h"

using namespace std;

int main() {
    //获取管理员权限
    WCHAR path[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, path, MAX_PATH);
    GainAdminPrivileges(path);

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
    if (my_gateway == legal_gateway) {
        cout << "网关核对正确..." << endl;
        // Compare MAC address
        string mac_address;
        getMAC(mac_address, my_gateway);
        cout << mac_address << mac_address.size() << endl;
        bool verify = compareMACAddress(mac_address);
        if (verify == false) {
            cout << "不存在于MAC地址清单中" << endl;
            string null_str;
            //execCmd("netsh interface set interface 以太网 disabled", null_str);
        }
        else {
            cout << "存在于MAC地址清单中" << endl;
            string null_str;
            //execCmd("netsh interface set interface 以太网 enabled", null_str);
        }
    }
    else {
        // Block the Network
        cout << "不存在对应网关地址" << endl;
        string null_str;
        //execCmd("netsh interface set interface 以太网 disabled", null_str);
    }
}
