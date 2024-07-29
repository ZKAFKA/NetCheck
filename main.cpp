#include"funcs.h"

using namespace std;

int main() {
    //��ȡ����ԱȨ��
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
        cout << "���غ˶���ȷ..." << endl;
        // Compare MAC address
        string mac_address;
        getMAC(mac_address, my_gateway);
        cout << mac_address << mac_address.size() << endl;
        bool verify = compareMACAddress(mac_address);
        if (verify == false) {
            cout << "��������MAC��ַ�嵥��" << endl;
            string null_str;
            //execCmd("netsh interface set interface ��̫�� disabled", null_str);
        }
        else {
            cout << "������MAC��ַ�嵥��" << endl;
            string null_str;
            //execCmd("netsh interface set interface ��̫�� enabled", null_str);
        }
    }
    else {
        // Block the Network
        cout << "�����ڶ�Ӧ���ص�ַ" << endl;
        string null_str;
        //execCmd("netsh interface set interface ��̫�� disabled", null_str);
    }
}
