
#pragma once

#include "File.h"


class QAloneFile : public IFile
{
public:
	QAloneFile(FILE* pFile);
	virtual ~QAloneFile();
//----IFile�ֿں�������ʼ----
	// ��ȡ�ļ�����
	unsigned long	Read(void* Buffer, unsigned long ReadBytes);
	// д���ļ�����
	unsigned long	Write(const void* Buffer, unsigned long WriteBytes);
	// ����ļ�����Buffer
	void*			GetBuffer();
	// �ƶ��ļ�ָ��λ�ã�Origin	-> Initial position: SEEK_CUR SEEK_END SEEK_SET
	long	Seek(long Offset, int Origin);
	// ȡ���ļ�ָ��λ��,ʧ�ܷ���-1��
	long	Tell();
	// ȡ���ļ�����,ʧ�ܷ���0��
	unsigned long	Size();

	// �жϴ򿪵��Ƿ��ǰ��е��ļ�
	int		IsFileInPak();
	//�ж��ļ��Ƿ�ֿ�ѹ����
	int		IsPackedByFragment();
	//��ȡ�ļ��ֿ����Ŀ
	int		GetFragmentCount();
	//��ȡ�ֿ�Ĵ�С
	unsigned int	GetFragmentSize(int nFragmentIndex);
	//��ȡһ���ļ��ֿ�
	unsigned long	ReadFragment(int nFragmentIndex, void*& pBuffer);

	// �رմ򿪵��ļ�
	void	Close();
	// �ӿڶ�������
	void	Release();
//----IFile�ֿں���������----

public:
	// ��һ���ļ���׼����ȡд
	static QAloneFile*	Open(const char* FileName, int WriteSupport = false);
	// ����һ���ļ���׼��д�롣
	static QAloneFile*	Create(const char*  FileName);

private:
	FILE*			m_hFile;				// �ļ�������
	void*			m_pContentBuffer;		// ���ݻ�����
	unsigned long	m_nContentBufferSize;	// ���ݻ�������С
};


