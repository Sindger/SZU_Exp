#include <iostream>
#include <windows.h>
#include <tchar.h>
using namespace std;
int main(){
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    char ReadBuff[100] = {0};
    DWORD ReadNum = 0;
    HANDLE hRead = NULL;
    HANDLE hWrite = NULL;
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = 0;
    BOOL bRet = CreatePipe(&hRead,&hWrite,&sa,0);
    if(bRet == TRUE){
        cout << "�ܵ������ɹ�"  << endl;
    }
    else{
        cout << "�����ܵ�ʧ�ܣ��������Ϊ��" << GetLastError() << endl;
    }
    HANDLE hTemp = GetStdHandle(STD_OUTPUT_HANDLE);
    SetStdHandle(STD_OUTPUT_HANDLE,hWrite);
    GetStartupInfo(&si);//��ȡ�����̵�ǰ��STARTUPINFO�ṹ��Ϣ
    si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
    //si.hStdInput = hRead;
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;
    bRet = CreateProcess(NULL,"Child.exe",NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi);
    SetStdHandle(STD_OUTPUT_HANDLE,hTemp);
    if(bRet == TRUE){
        cout << "�ɹ������ӽ���" << endl;
    }
    else{
        cout << "�����ӽ���ʧ�ܣ��������Ϊ ��" << GetLastError() << endl;
    }
    CloseHandle(hWrite);
    while(ReadFile(hRead,ReadBuff,100,&ReadNum,NULL)){
        ReadBuff[ReadNum] = '\0';
        cout << "�ӹܵ��ж���������" << ReadBuff << "��" << ReadNum << "�ֽ�����" << endl;
    }
    cin.get();
    return 0;
}