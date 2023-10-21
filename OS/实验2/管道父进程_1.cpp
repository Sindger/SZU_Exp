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
        cout << "管道创建成功"  << endl;
    }
    else{
        cout << "创建管道失败，错误代码为：" << GetLastError() << endl;
    }
    HANDLE hTemp = GetStdHandle(STD_OUTPUT_HANDLE);
    SetStdHandle(STD_OUTPUT_HANDLE,hWrite);
    GetStartupInfo(&si);//获取本进程当前的STARTUPINFO结构信息
    si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
    //si.hStdInput = hRead;
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;
    bRet = CreateProcess(NULL,"Child.exe",NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi);
    SetStdHandle(STD_OUTPUT_HANDLE,hTemp);
    if(bRet == TRUE){
        cout << "成功创建子进程" << endl;
    }
    else{
        cout << "创建子进程失败，错误代码为 ：" << GetLastError() << endl;
    }
    CloseHandle(hWrite);
    while(ReadFile(hRead,ReadBuff,100,&ReadNum,NULL)){
        ReadBuff[ReadNum] = '\0';
        cout << "从管道中读到的内容" << ReadBuff << "共" << ReadNum << "字节数据" << endl;
    }
    cin.get();
    return 0;
}