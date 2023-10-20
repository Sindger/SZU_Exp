#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <direct.h>
#include <boost/algorithm/string.hpp>
#include <boost/interprocess/streams/bufferstream.hpp>
#include <windows.h>

using namespace std;
using namespace boost;

void DoHelp() {
    cout << "HELP:This is a simple shell" << endl;
}

void DoExit() {
    cout << "EXIT:Simple shell will exit" << endl;
}

bool single_command(vector<string>& commands) {
    string command = commands[0];
    if (command == "help") {
        DoHelp();
        return true;
    }
    else if (command == "exit") {
        DoExit();
        exit(0);
    }
    else {
        for (int i = 1; i < commands.size(); i++) {
            command += " " + commands[i];
        }
        int state = system(command.c_str());
        return state == 0;
    }
    return false;
}

bool pipe_command(vector<vector<string>>&commands) {
    if (commands.size() == 0)
        return false;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    HANDLE read_handle = NULL;
    HANDLE writehandle = NULL;
    PROCESS_INFORMATION pipe;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    for (int i = 0; i < commands.size(); i++) {
        string cmd = "";
        for (int j = 0; j < commands[i].size(); j++) {
            if (j != commands[i].size())
                cmd += commands[i][j];
            cmd += commands[i][j] + " ";
        }
        if (i == 0) {
            CreatePipe(&read_handle, &writehandle, &sa, 0);
            si.hStdOutput = writehandle;
        }
        else if (i == commands.size() - 1) {
            CreatePipe(&read_handle, &writehandle, &sa, 0);
            si.hStdInput = read_handle;
        }
        else {
            HANDLE temphandle;
            CreatePipe(&temphandle, &writehandle, &sa, 0);
            CloseHandle(writehandle);
            writehandle = temphandle;
            si.hStdOutput = writehandle;
        }
        wstring wcmd = wstring(cmd.begin(), cmd.end());
        LPWSTR Lpwstr_cmd = const_cast<LPWSTR>(wcmd.c_str());
        if (!CreateProcess(NULL, Lpwstr_cmd, &sa, &sa, TRUE, 0, NULL, NULL, &si, &pipe)) {
            return false;
        }
        CloseHandle(pipe.hThread);
        if (read_handle != NULL) {
            CloseHandle(read_handle);
        }
        read_handle = writehandle;
    }
    DWORD Byte = 0;
    char buffer[1024];
    stringstream output_stream;
    while (ReadFile(read_handle, buffer, sizeof(buffer), &Byte, NULL)) {
        if (Byte == 0) {
            break;
        }
        output_stream.write(buffer, Byte);
    }
    string output_string = output_stream.str();
    return true;
}

void split_pipelines(const string &input, vector<string>& command_string) {
    istringstream iss(input);
    string token;
    while (iss >> token) {
        command_string.push_back(token);
    }
}

void get_input() {
    while (true) {
        cout << "Simple Shell>";
        string input;
        getline(cin, input);
        vector<string>command_string;
        split_pipelines(input, command_string);
        if (command_string.size()==0)
            continue;
        if (command_string[0] == "||") {
            cout << "此时不应有||" << endl;
            continue;
        }
        vector<vector<string>>pipelines;
        vector<string>pipeline;
        for (int i = 0; i < command_string.size(); i++) {
            if (command_string[i] == "||") {
                pipelines.push_back(pipeline);
                pipeline.clear();
            }
            else {
                pipeline.push_back(command_string[i]);
            }
        }
        pipelines.push_back(pipeline);
        if (pipelines.size() == 1) {
            if (pipelines[0].size() == 0)
                continue;
            bool state = single_command(pipelines[0]);
            if (!state)
                continue;
        }
        else {
            pipe_command(pipelines);
        }
    }
}

int main() {
    get_input();
    return 0;
}
