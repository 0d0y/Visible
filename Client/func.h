#pragma once

class GameObject;
class Fsm;
class Animation;

void CreateObject(GameObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(GameObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);
void ChangeFsmState(Fsm* _pFsm, PLAYER_STATE _eNextState);



template<typename T>
void SafeDeleteVector(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}


template<typename T1, typename T2>
void SafeDeleteMap(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}