
#pragma once

#include "CoreDeclspec.h"

#ifndef KD_MAX_MACADDRESS_LEN
	#define KD_MAX_MACADDRESS_LEN      8
#endif // KD_MAX_MACADDRESS_LEN

//�˺�����ȷ��������ַ����
//����ֵΪ��������
CORE_API int gGetMacAndIPAddress(
    unsigned char  *pMacAddressIn,  unsigned long *pIPAddressIn, 
    unsigned char  *pMacAddressOut, unsigned long *pIPAddressOut, 
    unsigned int uMask = 0x0000a8c0, 
    int nMacLength = 6
);

//��ȡ������IP�б�
//����ֵΪ��������
struct KADAPTER_MACADDRESS
{
	CHAR szMacAddress[KD_MAX_MACADDRESS_LEN];
};

CORE_API int gGetIPAddressList(
					KADAPTER_MACADDRESS* pMacAddressIns, DWORD* pdwIPAddressIns, DWORD& dwInIPCount, 
					KADAPTER_MACADDRESS* pMacAddressOuts, DWORD* pdwIPAddressOuts, DWORD& dwOutIPCount, 
					DWORD dwListCount, DWORD dwMask = 0x0000a8c0);

