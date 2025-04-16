#pragma once
#include<string>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include<dxcapi.h>
#include<wrl.h>
#include<map>
#include<memory>
#include"Model.h"
#include"ModelCommon.h"
#include"DirectXCommon.h"
class ModelManager
{
public:
	/*シングルトンインスタンスの取得*/
	static ModelManager* GetInstance();
	/*初期化*/
	void Initialize(DirectXCommon* dxCommon);
	/*モデルファイル読み込み*/
	void LoadModel(const std::string& filePath);
	/*終了*/
	void Finalize();

private:
	static ModelManager* instance;

	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(ModelManager&) = delete;
	ModelManager& operator=(ModelManager&) = delete;

	ModelCommon* modelCommon = nullptr;
	//モデルデータ
	std::map<std::string, std::unique_ptr<Model>>models;
};

