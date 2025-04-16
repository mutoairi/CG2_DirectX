#include "ModelManager.h"
ModelManager* ModelManager::instance = nullptr;

ModelManager* ModelManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new ModelManager();
	}
	return instance;
}

void ModelManager::Initialize(DirectXCommon* dxCommon)
{
	modelCommon = new ModelCommon;
	modelCommon->Initialize(dxCommon);
}

void ModelManager::Finalize()
{
	delete instance;
	instance = nullptr;
}
