
local self;		-- �ṩ���º����õ�UpValue

if MODULE_GAMESERVER then

-- tbItemInfo =
--{
--		nSeries or Env.SERIES_NONE,		���У�Ĭ����
--		nEnhTimes or 0,					ǿ��������Ĭ��0
--		nLucky or 0,					����
--		tbGenInfo,						
--		tbRandomInfo, 				װ�����Ʒ��
--		nVersion or 0,					
--		uRandSeed or 0,					�������
--		bForceBind,						ǿ�ư�Ĭ��0
--		bTimeOut,						�Ƿ�ᳬʱ
-- 		bMsg,							�Ƿ���Ϣ֪ͨ
--}	

function _KLuaPlayer.AddItemEx(nGenre, nDetail, nParticular, nLevel, nWay)
	
	nGenre 		= tonumber(nGenre) or 0;
	nDetail 	= tonumber(nDetail) or 0;
	nParticular = tonumber(nParticular) or 0;
	nLevel 		= tonumber(nLevel) or 0;
	
	return	KItem.AddPlayerItem(
		self,
		nGenre,
		nDetail,
		nParticular,
		nLevel,
		1
	);
end

end

