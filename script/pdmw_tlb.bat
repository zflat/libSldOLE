
:: find program id
:: https://forum.solidworks.com/thread/41467
regsvr32 "C:\Program Files\Common Files\SolidWorks Shared\pdmworks.dll"
:: regsvr32 "C:\Program Files\Common Files\SolidWorks Shared\PDMWorks.Interop.pdmworks.dll"


:: Use a dll for type library
:: https://qt-project.org/forums/viewthread/13347
::C:\Windows\Microsoft.NET\Framework64\v4.0.30319\RegAsm.exe "C:\Program Files\SolidWorks Corp\SolidWorks\api\redist\PDMWorks.Interop.pdmworks.dll" /tlb:pdmw.tlb
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\RegAsm.exe "C:\Program Files\Common Files\SolidWorks Shared\PDMWorks.Interop.pdmworks.dll" /tlb


pause
