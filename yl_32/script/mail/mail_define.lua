--
-- FileName: mail_define.lua
-- Author: 	 xiewenzhe
-- Time: 	 2011/5/25 10:32
-- Comment:	
--

if not (MODULE_GAMECLIENT or MODULE_GAMESERVER) then
	return
end

Mail.MAIL_COST = 100				-- ����
Mail.SEND_LIMIT = 10000				-- һ�췢���ʼ������ƴ���(������˰ɣ�����������Կ����������)
Mail.MAX_PLAYER_COUNT = 20			-- �������ʼ�����

-- �ʼ�ͼ��
Mail.ICONID_PLAYER = 1				-- ����ʼ�ͼ��

-- �ʼ�������Ϣ
Mail.FAILREASON_UNKNOWN = 0			-- δ֪ԭ��
Mail.FAILREASON_BOXFULL = 1			-- ��������
Mail.FAILREASON_RECEIVER = 2		-- �ռ��˴���
Mail.FAILREASON_MONEY = 3			-- ��Ǯ����
Mail.FAILREASON_ITEM = 4			-- ��Ʒ����
Mail.FAILREASON_FORBID = 5			-- ��ֹ����
Mail.FAILRESON_DELIVERY = 6			-- ��������

-- �����ʼ��б�����
Mail.MAILLIST_PLAYER = 1			-- ����ʼ�
Mail.MAILLIST_SYSTEM = 2			-- ϵͳ�ʼ�

-- �ʼ�����
Mail.TYPE_SYSTEM = 0				-- ϵͳ�ʼ�
Mail.TYPE_PLAYER = 1				-- ����ʼ�
Mail.TYPE_DELIVERY = 2				-- ����

-- �ʼ�����������
Mail.SEND_TYPE_PLAYER = 0			-- ��ҷ���
Mail.SEND_TYPE_SYSTEM = 1			-- ϵͳ����

-- �ʼ����������Ĳ���
Mail.COND_OP_IGNORE = 0				-- ����
Mail.COND_OP_GREATER = 1			-- ����
Mail.COND_OP_GREATEREQUAL = 2		-- ���ڵ���
Mail.COND_OP_LESS = 3				-- С��
Mail.COND_OP_LESSEQUAL = 4			-- С�ڵ���
Mail.COND_OP_EQUAL = 5				-- ����
Mail.COND_OP_NOTEQUAL = 6			-- ������