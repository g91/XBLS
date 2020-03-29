// xshell account creation released by xbLive team :)
// NOTE: Utils::vaw is the equiv of va, but unicode. PASSWORD MUST BE NO LONGER THAN 11, EMAIL MUST BE NO LONGER THAN 12

if (server.bDevkit) {
    *(DWORD*)0x817a69CC = 0x60000000;

    wchar_t buffer[15];
    lstrcpyW(buffer, L"%s@");
    lstrcatW(buffer, Utils::vaw(Config::szXShellEmail));

    lstrcpyW((wchar_t*)0x8160E254, buffer);
    lstrcpyW((wchar_t*)0x8160E23C, Utils::vaw(Config::szXShellPassword));

    char buffer2[16];
    strcpy(buffer2, "%ws@");
    strcat(buffer2, Config::szXShellEmail);

    strcpy((char*)0x8160D8E4, buffer2);
    strcpy((char*)0x8160D898, Utils::va("@%s", Config::szXShellEmail));
    strcpy((char*)0x8160D858, Config::szXShellPassword);
}