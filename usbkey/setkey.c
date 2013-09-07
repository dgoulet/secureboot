#include <efi.h>
#include <efilib.h>

#define BUFSIZE 2048


EFI_STATUS efi_main (EFI_HANDLE image, EFI_SYSTEM_TABLE *systab) {
    CHAR16 Data[BUFSIZE];
    UINTN DataSize = 0;
    UINTN Attr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
    EFI_GUID Guid = (EFI_GUID){ 0xd719b2cb, 0x3d3a, 0x4596,
                                    {0xa3,0xbc,0xda,0xd0,0x0e,0x67,0x65,0x6f}};
    EFI_STATUS status = EFI_SUCCESS;

    InitializeLib(image, systab);

    ZeroMem(Data, BUFSIZE);
    StrCpy(Data, L"stgraber_debug: abcdef\n");
    DataSize = StrLen(Data) * 2;

    status = uefi_call_wrapper(RT->SetVariable, 5, L"bootme_flag",
                        &Guid, Attr, DataSize, &Data);

    if (status != EFI_SUCCESS)
        Print(L"ERROR: SetVariable failed: %d\n", status);
    else
        Print(L"Variable set to: %s\n", Data);

    return status;
}
