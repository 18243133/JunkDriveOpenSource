#ifndef _RSA_
#define _RSA_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WINNT
#include <ntifs.h>
#include <ntddk.h>
#define DPRINT(format, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, format, __VA_ARGS__)
#define GetMem(size) ExAllocatePoolWithTag(NonPagedPool, size, 'lkey');
#define FreeMem(p) ExFreePoolWithTag(p, 'lkey');
#else
#include <stdio.h>
#include <windows.h>

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

#define STATUS_UNSUCCESSFUL              ((NTSTATUS)0xC0000001L)
//#define STATUS_INVALID_PARAMETER         ((NTSTATUS)0xC000000DL)    // winnt

#define DPRINT(format, ...) printf(format, __VA_ARGS__);
#define GetMem(size) malloc(size);
#define FreeMem(p) free(p);
#endif // !_USER_MODE

#include <bcrypt.h>

#ifndef DWORD 
#define DWORD ULONG
#endif

/*
�ܼ��ܵ����ݳ���ȡ������Կ��bit
�������Ϊ ��Կbit / 8
512bit:  64
1024bit: 128
2048bit: 256
4096bit: 512

��Ӧ��
512bit��Կ:
��Կ����:91 ˽Կ155
1024bit��
��Կ:155 ˽Կ283
2048bit��
��Կ:283 ˽Կ539
4096bit:
��Կ:539 ˽Կ1051
*/

/*
����RSA��Կ ֧������ 512 1024 2048 4096bit ��Կ
�������ڲ����� �ⲿ�ͷ�
RSAGenerateKey:
dwKeyLen : 512 , 1024 , 2048, 4096 ����һ��
lpPubKey : ���ع�Կָ�� ʹ�������caller�ͷ�
lpcbPubKey : ���ع�Կ����
lpPrivKey : ����˽Կָ�� ͬ2
lpcbPriv : ����˽Կ����
����ֵ: NTSTATUS ֵ
*/
NTSTATUS RSAGenerateKey(DWORD dwKeyLen, PVOID* lpPubKey, DWORD* lpcbPubKey, PVOID* lpPrivKey, DWORD* lpcbPriv);

/*
RSA��Կ����
RSAEncrypt:
PublicKey: ��Կ��ŵ�ַ
cbPublicKey : ��Կ���� (������Ȳ����ϻ᷵����Ч����)
encryptData : ���ܵ�����
cbEncryptData : �������ݵĳ���
lpEncryped : ���ؼ��ܺ������ָ�� ʹ�������caller�ͷ�
lpCbEncrypt : ���ؼ��ܺ����ݵĳ���
*/
NTSTATUS RSAEncrypt(PUCHAR PublicKey, DWORD cbPublicKey, PUCHAR encryptData, DWORD cbEncryptData, PVOID* lpEncryped, DWORD* lpCbEncrypt);

/*
RSA˽Կ����
RSADecrypt:
PrivateKey: ˽Կ
cbPrivateKey �� ˽Կ���� (������Ȳ����ϻ᷵����Ч����)
decryptData : Ҫ���ܵ�����
cbDecryptData : Ҫ�������ݵĳ���
lpDecrypted : ���ؽ���֮������ָ�� ʹ�������caller�ͷ�
lpCbDecrypted : ���ؽ���֮�����ݵĳ���
*/
NTSTATUS RSADecrypt(PUCHAR PrivateKey, DWORD cbPrivateKey, PUCHAR decryptData, DWORD cbDecryptData, PVOID* lpDecrypted, DWORD* lpCbDecrypted);

#ifdef __cplusplus
}
#endif

#endif