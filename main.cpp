#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

bool isSpotify(const PROCESSENTRY32W &entry) {
    return std::wstring(entry.szExeFile) == L"Spotify.exe";
}

BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam) {
    const auto &pids = *reinterpret_cast<vector<DWORD>*>(lParam);

    DWORD winId;
    GetWindowThreadProcessId(hwnd, &winId);

    for (DWORD pid : pids) {
        if (winId == pid) {
            wstring title(GetWindowTextLength(hwnd) + 1, L'\0');
            GetWindowTextW(hwnd, &title[0], title.size()); //note: C++11 only

            if(title.find('-') != string::npos) {
                wcout << "Song: " << title << "\n\n";
            }
        }
    }

    return TRUE;
}

int main() {
    vector<DWORD> pids;

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof entry;

    if (!Process32FirstW(snap, &entry)) {
        return 0;
    }

    do {
        if (isSpotify(entry)) {
            pids.emplace_back(entry.th32ProcessID);
        }
    } while (Process32NextW(snap, &entry));


    EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&pids));
}