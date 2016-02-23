-----------------------------------------------------
--�ļ���		��	relation_client.lua
--������		��	
--����ʱ��		��	
--��������		��	�˼ʹ�ϵclient_core�ű���
------------------------------------------------------


Relation.SORTTYPE =
{
	Player.emKPLAYERRELATION_TYPE_BIDFRIEND,
	Player.emKPLAYERRELATION_TYPE_TRAINING,
	Player.emKPLAYERRELATION_TYPE_TRAINED,
	Player.emKPLAYERRELATION_TYPE_COUPLE,
	Player.emKPLAYERRELATION_TYPE_INTRODUCTION,
	Player.emKPLAYERRELATION_TYPE_BUDDY,
};

Relation.MAX_NUMBER_FRIEND	= 200;
----------------------------

function Relation:SyncRelationStart()
	me.Relation_InitRelationList();
end

-- ͬ���˼ʹ�ϵ�б�
function Relation:SyncRelationList(tbList)
	for nIndex in pairs(tbList) do
		-- �������ͣ������ݽ��з���
		me.Relation_AddRelation(tbList[nIndex])
	end
	CoreEventNotify(UiNotify.emCOREEVENT_RELATION_UPDATEPANEL);
end

function Relation:SyncAddRelationList(tbList)
	for nIndex in pairs(tbList) do
		-- �������ͣ������ݽ��з���
		me.Relation_AddRelation(tbList[nIndex])
	end
	CoreEventNotify(UiNotify.emCOREEVENT_RELATION_UPDATEPANEL);
end

function Relation:SyncRelationInfo(tbInfoList)
	if not tbInfoList then
		return 0;
	end
	
	for i = 1, #tbInfoList do
		me.Relation_SetRelationInfo(tbInfoList[i].szPlayer, tbInfoList[i]);
	end
	CoreEventNotify(UiNotify.emCOREEVENT_RELATION_REFRESHTRAIN);
	CoreEventNotify(UiNotify.emCOREEVENT_RELATION_UPDATEPANEL);
end

-- ����˼ʹ�ϵ
function Relation:OnAddRelation(szPlayer, nType)
	if me.HasRelation(szPlayer, 4) == 1 then
		me.Msg(Lang.gcscript.str47[Lang.Idx])
		return
	end
	local tbRelationList, tbInfo, nNum = me.Relation_GetRelationList();
	if ((nType == Player.emKPLAYERRELATION_TYPE_BIDFRIEND or nType == Player.emKPLAYERRELATION_TYPE_TMPFRIEND) and
		nNum and self.MAX_NUMBER_FRIEND <= nNum) then
		me.Msg(Lang.gcscript.str48[Lang.Idx]);
		return;
	end
	
	me.CallServerScript({"RelationCmd", "AddRelation_C2S", szPlayer, nType});
end

-- ɾ���˼ʹ�ϵ
function Relation:DelRelation(szPlayer, nType)
	local tbDel = me.Relation_DelRelation(nType, szPlayer)
	if not tbDel then
		return;
	end
	if (tbDel.nType == Player.emKPLAYERRELATION_TYPE_TRAINED or
		tbDel.nType == Player.emKPLAYERRELATION_TYPE_TRAINING or 
		tbDel.nType == Player.emKPLAYERRELATION_TYPE_BUDDY or
		tbDel.nType == Player.emKPLAYERRELATION_TYPE_INTRODUCTION or
		tbDel.nType ==  Player.emKPLAYERRELATION_TYPE_COUPLE) then
		tbDel.nType = Player.emKPLAYERRELATION_TYPE_BIDFRIEND;
		me.Relation_AddRelation(tbDel);
	end
	CoreEventNotify(UiNotify.emCOREEVENT_RELATION_UPDATEPANEL);
end

function Relation:UpdateTrainingOption(nTeacher, nStudent)
	CoreEventNotify(UiNotify.emCOREEVENT_SYNC_TRAINING_OPTION, nTeacher, nStudent);
end
function Relation:SelfCheckInTime(nCheckTime)
-- 	me.SetMySelfCheckTime(nCheckTime);
--	CoreEventNotify(UiNotify.emCOREEVENT_SELF_CHECKIN_TIME);
end

-- �����ʦ
function Relation:CmdApplyTeacher(szPlayerName)
	me.CallServerScript({"RelationCmd", "ApplyTeacher_C2S", szPlayerName});
end

-- �����ʦ
function Relation:ApplyTeacher_S2C(szPlayerName)
	if (not szPlayerName) then
		return;
	end
	CoreEventNotify(UiNotify.emCOREEVENT_TRAINING_APPLYFORTEACHER, szPlayerName);
end

---------------------------------------------------------------------------------------
-- �����˼ʹ�ϵ�ж���relation.lua�б���һ��(������ʱ����)

-- �Ƿ�Ϊ������ҵĺ��� ��������ʱ����
function Relation:IsFriend(szPlayer)
	local tbRelationList, _ = me.Relation_GetRelationList();
	if (not tbRelationList) then
		return 0;
	end
	local tbFriendList = tbRelationList[Player.emKPLAYERRELATION_TYPE_BIDFRIEND];
	if (tbFriendList) then
		for szName, tbFriend in pairs(tbFriendList) do
			if (szName == szPlayer) then
				return 1;
			end
		end
	end
	-- ������
	local tbIntroducerList = tbRelationList[Player.emKPLAYERRELATION_TYPE_INTRODUCTION];
	if (tbIntroducerList) then
		for szName, tbIntroducer in pairs(tbIntroducerList) do
			if (szName == szPlayer and tbIntroducer.nRole == 1) then
				return 1;
			end
		end
	end
	return 0;
end

-- �Ƿ�Ϊ������ҵĶ��� 
function Relation:IsTeammate(szPlayer)
	local nAllotModel, tbMemberList = me.GetTeamInfo();
	if (not tbMemberList) then
		return 0;
	end
	for i = 1, #tbMemberList do
		if (szPlayer == tbMemberList[i].szName) then
			return 1;
		end
	end
	return 0;
end

-- �Ƿ��뱾�������ʦͽ��ϵ
function Relation:IsTrainRelation(szPlayer)
	local tbRelationList, _ = me.Relation_GetRelationList();
	if (not tbRelationList) then
		return 0;
	end
	-- δ��ʦ
	local tbTrainingList = tbRelationList[Player.emKPLAYERRELATION_TYPE_TRAINING];
	if (tbTrainingList) then
		for szName, _ in pairs(tbTrainingList) do
			if (szName == szPlayer) then
				return 1;
			end
		end
	end
	-- �ѳ�ʦ
	local tbTrainedList = tbRelationList[Player.emKPLAYERRELATION_TYPE_TRAINED];
	if (tbTrainedList) then
		for szName, tbTrained in pairs(tbTrainedList) do
			if (szName == szPlayer) then	
				return 1;
			end
		end
	end
	return 0;
end

-- �Ƿ�Ϊ������ҵ�����
function Relation:IsBuddy(szPlayer)
	local tbRelationList, _ = me.Relation_GetRelationList();
	if (not tbRelationList) then
		return 0;
	end
	-- ����
	local tbBuddyList = tbRelationList[Player.emKPLAYERRELATION_TYPE_BUDDY];
	if (tbBuddyList) then
		for szName, _ in pairs(tbBuddyList) do
			if (szName == szPlayer) then
				return 1;
			end
		end
	end
	-- ������
	local tbIntroducerList = tbRelationList[Player.emKPLAYERRELATION_TYPE_INTRODUCTION];
	if (tbIntroducerList) then
		for szName, tbIntroducer in pairs(tbIntroducerList) do
			if (szName == szPlayer and tbIntroducer.nRole == 0) then
				return 1;
			end
		end
	end
	return 0;
end

-- ʦ��Ϊ������ҵ�����
function Relation:IsCouple(szPlayer)
	local tbRelationList, _ = me.Relation_GetRelationList();
	if (not tbRelationList) then
		return 0;
	end
	-- ����
	local tbCoupleList = tbRelationList[Player.emKPLAYERRELATION_TYPE_COUPLE];
	if (tbCoupleList) then
		for szName, _ in pairs(tbCoupleList) do
			if (szName == szPlayer) then
				return 1;
			end
		end
	end
	return 0;
end
