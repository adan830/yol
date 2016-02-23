--
-- FileName: mail_c.lua
-- Author: 	 xiewenzhe
-- Time: 	 2011/5/25 9:40
-- Comment:	 �ʼ�(Client)
--

if not MODULE_GAMECLIENT then
	return
end

-------------------------------------------------- ����API -------------------------------------
-----------------------------------------
--  ��������ʼ�
--	tbMailInfo��ʽ��
--	tbMailInfo.tbReceiver	�ռ����б�
-- 	tbMailInfo.szCaption	�ʼ�����
--  tbMailInfo.szContent	�ʼ�����
--  tbMailInfo.tbItem		�ʼ�����������ʼ����ܷ��͸�����
------------------------------------------
function Mail:SendMail(tbMailInfo)
	if (not tbMailInfo) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Mail", "�����ʼ���ϢΪ��!")
		return
	end
	
	-- ����ռ���
	local bCheckReceiver = 1
	local nReceiverCount = #tbMailInfo.tbReceiver
	if (not tbMailInfo.tbReceiver or nReceiverCount == 0) then
		bCheckReceiver = 0
	else
		for _, szReceiver in pairs(tbMailInfo.tbReceiver) do
			if (not szReceiver or type(szReceiver) ~= "string") then
				bCheckReceiver = 0
				break
			end
		end
	end
	if (bCheckReceiver == 0) then
		return self:OnSendResult(0, self.FAILREASON_RECEIVER)
	end
	tbMailInfo.tbReceiver.nCount = nReceiverCount
	
	-- ��������Ƿ�
	local nMoney = me.pPlayerPurse.GetMoney(Purse.EM_MONEY_SILVER)
	if (nMoney < nReceiverCount * self.MAIL_COST) then
		return self:OnSendResult(0, self.FAILREASON_MONEY)
	end
	
	-- ����
	me.pMail.SendMail(self.ICONID_PLAYER, Mail.TYPE_PLAYER, tbMailInfo.tbReceiver, tbMailInfo.szCaption, tbMailInfo.szContent)
end

-----------------------------------------
--  ���ͼ���
--	tbMailInfo��ʽ��
--	tbMailInfo.tbReceiver	�ռ����б�
-- 	tbMailInfo.szCaption	�ʼ�����
--  tbMailInfo.szContent	�ʼ�����
--  tbMailInfo.tbItem		�ʼ��������������ܷ��͸�����
------------------------------------------
function Mail:DeliveryMail(tbMailInfo)
	if (not tbMailInfo) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Mail", "������ϢΪ��!")
		return
	end
	
	-- ����ռ���
	local bCheckReceiver = 1
	local nReceiverCount = #tbMailInfo.tbReceiver
	if (not tbMailInfo.tbReceiver or nReceiverCount == 0) then
		bCheckReceiver = 0
	else
		for _, szReceiver in pairs(tbMailInfo.tbReceiver) do
			if (not szReceiver or type(szReceiver) ~= "string") then
				bCheckReceiver = 0
				break
			end
		end
	end
	if (bCheckReceiver == 0) then
		return self:OnSendResult(0, self.FAILREASON_RECEIVER)
	end
	tbMailInfo.tbReceiver.nCount = nReceiverCount
	
	-- ����
	me.pMail.SendMail(self.ICONID_PLAYER, Mail.TYPE_DELIVERY, tbMailInfo.tbReceiver, tbMailInfo.szCaption, tbMailInfo.szContent)
end

-- �����ʼ��б�
function Mail:RequestMailList(nType)
	me.pMail.RequestMailList(nType)
end

-- �����ʼ���������
function Mail:RequestMail(nMailId)
	if (not nMailId) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Mail", "�����ʼ�IdΪ��!")
		return
	end
	
	me.pMail.RequestMail(nMailId)
end

-- �����ȡ����
function Mail:FetchItem(nMailId, nItemIndex)
	if (not nMailId or
		not  nItemIndex or
		type(nItemIndex) ~= "number") then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Mail", "�����ʼ�������������ȷ!")
		return
	end
	
	me.pMail.FetchItem(nMailId, nItemIndex)
end

-- ����ɾ���ʼ�
function Mail:DeleteMail(nMailId)
	if (not nMailId) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Mail", "����ɾ���ʼ�IdΪ��!")
		return
	end
	
	me.pMail.DeleteMail(nMailId)
	if (self.tbDelivery and self.tbDelivery[nMailId]) then
		self.tbDelivery[nMailId] = nil
	end
end

-------------------------------------------------- GS������Ӧ ----------------------------------
function Mail:Init()
	self.tbMailList = {}
	self.tbMailContent = {}
end

-- ����������
function Mail:OnMailBoxLoadOK(bShowMsg)
	if (bShowMsg and bShowMsg == 1) then
--		me.SysMsg("�ż�������ɣ�")
	end
	
	self:Init()
	CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_LOADOK)
end

-- ͬ���ʼ��б�
function Mail:OnFetchMailList(tbMailList)
	if (not tbMailList) then
		return
	end
	
	-- ��ʱ���Ⱥ�����δ���ʼ�������
	self.tbMailList = {}
	for _, tbMailInfo in pairs(tbMailList) do
		if (not self.tbMailList[1]) then
			table.insert(self.tbMailList, tbMailInfo)
		else
			local bFind = false
			for nIndex, tbInsert in ipairs(self.tbMailList) do
				if (tbMailInfo.nState == tbInsert.nState) then
					if (tbMailInfo.nTime > tbInsert.nTime) then
						table.insert(self.tbMailList, nIndex, tbMailInfo)
						bFind = true
						break
					end
				else
					if (tbMailInfo.nState == 0) then
						table.insert(self.tbMailList, nIndex, tbMailInfo)
						bFind = true
						break
					end
				end
			end
			
			if (not bFind) then
				table.insert(self.tbMailList, tbMailInfo)
			end
		end
	end
	
	CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_SYNCLIST)
	
	-- ���Խű�
	--me.SysMsg("ͬ���ʼ��б�")
	--print("~~~~~~~~~~~~~~~~~~~~ �ʼ��б�")
	--for i, tbInfo in ipairs(self.tbMailList) do
		--print(string.format("[%d] mail", i))
		--print("nMailId: " .. tbInfo.nMailId)
		--print("nState: " .. tbInfo.nState)
		--print("nType: " .. tbInfo.nType)
		--print("nIconId: " .. tbInfo.nIconId)
		--print("szCatpion: " .. tbInfo.szCaption)
		--print("szReceiver: " .. tbInfo.szReceiver)
		--print("szSender: " .. tbInfo.szSender)
		--print("nTime: " .. tbInfo.nTime)
	--end
end

function Mail:GetMailList()
	return self.tbMailList
end

-- ���»�����ʼ�״̬
function Mail:ChangeState(nMailId, nState)
	local tbMailInfo = nil
	local bFind = 0
	for _, tbOne in pairs(self.tbMailList) do
		if (tbOne.nMailId == nMailId) then
			tbMailInfo = tbOne
			bFind = 1
			break
		end
	end
	if (bFind == 0) then
		Dbg:WriteLogEx(Dbg.LOG_ERROR, "Mail", "ָ���ʼ������ڵ�ǰ�ʼ��б��У��޷��ı�״̬!")
		return
	end
	
	tbMailInfo.nState = nState
end

function Mail:GetDeliveryMailById(nMailId)
	return self.tbDelivery[nMailId]
end

-- ͬ���ʼ�����
function Mail:OnFetchMail(tbMailContent)
	if (not tbMailContent) then
		return
	end
	
	if (not self.tbDelivery) then
		self.tbDelivery = {}
	end
	
	if (tbMailContent.nType == Mail.TYPE_DELIVERY) then
		self.tbDelivery[tbMailContent.nMailId] = tbMailContent
		CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_NEWDELIVERY, tbMailContent.nMailId)
	else
		self.tbMailContent = tbMailContent
		CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_SYNCCONTENT, tbMailContent.nMailId)
	end
	
	-- ���Խű�
	--me.SysMsg("ͬ���ʼ�����")
	--print("~~~~~~~~~~~~~~~~~~~~ �ʼ����ݣ�")
	--print("nMailId: " .. tbMailContent.nMailId)
	--print("nIconId: " .. tbMailContent.nIconId)
	--print("szContent: " .. tbMailContent.szContent)
	--if (tbMailContent.tbItem) then
		--print("tbItem: ")
		--for i, tbInfo in ipairs(tbMailContent.tbItem) do
			--print(string.format("[%d] item", i))
			--print("nItemIndex: " .. tbInfo.nItemIndex)
			--print("nClassId: " .. tbInfo.nClassId)
			--print("nCount: " .. tbInfo.nCount)
			--print("nPrice: " .. tbInfo.nPrice)
			--print("nStateFlags: " .. tbInfo.nStateFlags)
			--print("nTimeoutType: " .. tbInfo.nTimeoutType)
			--print("nTimeout: " .. tbInfo.nTimeout)
		--end
	--end
end

function Mail:GetMailContent()
	return self.tbMailContent
end

--�������ͽ��
function Mail:OnSendDeliveryResult(nResult)
	Shop:OnSendClaimResult(nResult or 0)
end

-- �ʼ����ͽ��
function Mail:OnSendResult(nResult, nReasonType, szFailReason)
	local szMsg = ""
	if (nResult == 1) then
		-- ���ͳɹ�
		szMsg = Lang.mail.str1[Lang.Idx]
		me.SysMsg(szMsg)
	else
		-- ����ʧ��
		szMsg = Lang.mail.str2[Lang.Idx]
		if (nReasonType == self.FAILREASON_BOXFULL) then
			szMsg = szMsg .. Lang.mail.str3[Lang.Idx]
		elseif (nReasonType == self.FAILREASON_RECEIVER) then
			if (not szFailReason or type( szFailReason) ~= "string") then
				szMsg = szMsg .. Lang.mail.str4[Lang.Idx]
			else
				szMsg = szMsg .. szFailReason
			end
		elseif (nReasonType == self.FAILREASON_MONEY) then
			szMsg = szMsg .. Lang.mail.str5[Lang.Idx]
		elseif (nReasonType == self.FAILREASON_ITEM) then
			szMsg = szMsg .. Lang.mail.str6[Lang.Idx]
		elseif (nReasonType == self.FAILREASON_FORBID) then
			if (not  szFailReason or type( szFailReason) ~= "string") then
				szMsg = szMsg .. Lang.mail.str7[Lang.Idx]
			else
				szMsg = szMsg .. szFailReason
			end
		else
			szMsg = szMsg .. Lang.mail.str8[Lang.Idx]
		end
		
		me.SysMsg(szMsg)
	end
	
	CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_SENDRESULT, nResult, szMsg)
end

-- ���ʼ�֪ͨ
function Mail:OnNewMail()
	me.SysMsg(Lang.mail.str9[Lang.Idx])
	CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_NEW)
	
	-- �����ʼ�ʱ������һ���ʼ��б�
	self:RequestMailList(self.MAILLIST_SYSTEM)
end

-- ��ȡ�����ɹ�
function Mail:OnFetchItemOK(nMailId, nItemIndex)
	CallCenter:OnEvent(KOBJEVENT.emKOBJEVENTTYPE_MAIL_FETCHITEMOK, nMailId, nItemIndex)
end
