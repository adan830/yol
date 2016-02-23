
#pragma once

enum LOG_RECORD_REMIND_LEVEL
{
	LOG_LEVEL_INFO		= 0x1,
	LOG_LEVEL_ATTENTION	= 0x2,
	LOG_LEVEL_WARNING		= 0x4,
	LOG_LEVEL_ERROR		= 0x8,
};

struct _QLog_SystemTime 
{
	int	Hour;
	int	Minute;
	int	Second;
};

class CORE_API QLogFile
{
public:
	enum KLogFileParam
	{
		MAX_LINE_LEN = 2048,
	};
	///�����ʹ�õĽӿ�
public:
	QLogFile();
	virtual ~QLogFile();

	///brief ָ��LOG�ļ��Ĵ��·�����Լ�ÿ��LOG�ļ��Ĵ�С
	int		InitialLogFile(const char* strRootPath, const char* strFilePrefix, size_t nSize = 0x100000);

	///������¼LOG�ļ�,����LOG_ATTENTION��LOG_WARNING��LOG_ERROR�������������������ʾ�Ƿ��¼��������log��¼
	int		FinishLogFile();

	//��ǰ�򿪵�LOG�ļ���д��һ����Ϣ
	//�������nInfoLen��ʾszInfo�ַ����ĳ��ȣ���������β���������븺����ʾ�ַ�����'\0'�ַ���β��
	void	LogRecord(LOG_RECORD_REMIND_LEVEL nRemindLevel, const char* szInfo, int nInfoLen = -1);
	//��¼�Զ��ı���ʽ���ַ���
	void	LogRecordVar(LOG_RECORD_REMIND_LEVEL nRemindLevel, const char* szInfoFmt, ...);

	//���԰汾�������LOG
	void	DebugLogRecord(LOG_RECORD_REMIND_LEVEL nRemindLevel, const char* szInfo, int nInfoLen = -1);
	//��¼�Զ��ı���ʽ���ַ���
	void	DebugLogRecordVar(LOG_RECORD_REMIND_LEVEL nRemindLevel, const char* szInfoFmt, ...);

	///��ѯ��ǰLOGģ���Ƿ��д�����������LOG_ATTENTION��LOG_WARNING��LOG_ERROR�������������������ʾ�Ƿ��¼��������log��¼
	int		QueryState();

	//�жϵ�ǰlogģ������д��������������ʾ������Ϣ
	void	StateNotifyUi();

	///�ڲ�ʵ��
private:
	///�½�һ��LOG�ļ�
	int		PrepareLogFile();

	///�رյ�ǰ���ڼ�¼��LOG�ļ�
	int		CloseLogFile();

	///Attribs
private:
	IFile*			m_pFile;
	char			m_szFullname[MAX_PATH];
	char			m_strRoot[64];
	char			m_strFilePrefix[64];

	size_t			m_nMaxSize;
	int				m_bCurrentError;
	int				m_bCurrentWarning;

	int				m_nCurrentVersion;
	_QLog_SystemTime		m_nCurrentTime;
	int				m_nCurrentState;
};
