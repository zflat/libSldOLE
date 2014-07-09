#include "sld_app_context.h"


SldAppContext::~SldAppContext()
{
}

SldAppContext::SldAppContext()
{
    HRESULT hres;

    int proc_count = 0;
    // http://stackoverflow.com/questions/865152/how-can-i-get-a-process-handle-by-its-name-in-c
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            size_t   i;
            int nSize = 261;
            char *pAnsiString = new char[nSize];
            wcstombs_s(&i, pAnsiString, (size_t)nSize, entry.szExeFile, (size_t)nSize);

            if (_stricmp(pAnsiString, "SLDWORKS.exe") == 0)
            {
                proc_count++;
                if(false){
                    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                    CloseHandle(hProcess);
                }
            }
        }
    }
    CloseHandle(snapshot);


    if(proc_count == 1){
        hres = swApp.CreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER);
        if (FAILED(hres)){
            qWarning() << " Could not CreateInstance(__uuidof(SldWorks)";
            return;
        }
    }
}

ISldWorksPtr SldAppContext::getApp(){
    return swApp;
}
