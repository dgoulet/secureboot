#include <efi.h>
#include <efilib.h>

#define BUFSIZE 2048

static EFI_STATUS set_variable (CHAR16 *name, CHAR16 *data)
{
   EFI_STATUS  Status  = EFI_SUCCESS;
   EFI_GUID Guid = (EFI_GUID){ 0xd719b2cb, 0x3d3a, 0x4596,
                              {0xa3,0xbc,0xda,0xd0,0x0e,0x67,0x65,0x6f}};
   UINTN       VarSize;

   if (NULL == data) {
       return EFI_INVALID_PARAMETER;
   }

   VarSize = (StrLen (data) + 1) * sizeof (CHAR16);
   Status = RT->SetVariable (name,
                            &Guid,
                            EFI_VARIABLE_BOOTSERVICE_ACCESS|EFI_VARIABLE_RUNTIME_ACCESS|EFI_VARIABLE_NON_VOLATILE,
                            VarSize,
                            data);
   return Status;
}

EFI_STATUS efi_main (EFI_HANDLE image, EFI_SYSTEM_TABLE *systab) {
    EFI_STATUS status = EFI_SUCCESS;

    InitializeLib(image, systab);
    status = set_variable(L"OurSecretVariable", L"abcdefg");

    return status;
}
