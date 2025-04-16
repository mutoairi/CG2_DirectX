#include<Windows.h>
#include<cstdint>
#include<string>
#include<format>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<dxgidebug.h>
#include<dxcapi.h>
#include<math.h>
#include<fstream>
#include<sstream>
#include<wrl.h>
#include<list>
#include"Input.h"
#include"WinApp.h"
#include "DirectXCommon.h"
#include"D3DResourceLeakChecker.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"Object3dCommon.h"
#include"Object3d.h"
#include"ModelCommon.h"
#include"Model.h"
#include"TextureManager.h"
#include"ModelManager.h"
#include"StringUtility.h"
#include"Logger.h"

#include"makeMatrix.h"
#include"externals/imugui/imgui.h"
#include"externals/imugui/imgui_impl_dx12.h"
#include"externals/imugui/imgui_impl_win32.h"
#include"externals/DirectXTex/DirectXTex.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxcompiler.lib")




//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	CoInitializeEx(0, COINIT_MULTITHREADED);
	D3DResourceLeakChecker leakChack;
#pragma region"ウィンドウの生成"

	WinApp* winApp = nullptr;
	winApp = new WinApp();
	winApp->Initialize();


	;

#pragma endregion

#pragma region"DXCCommonの生成"

	//ポインタ
	DirectXCommon* dxcCommon = nullptr;
	//DirectXの初期化
	dxcCommon = new DirectXCommon();
	dxcCommon->Initialize(winApp);
	//HRESULT hr;





		//ポインタ
	Input* input = nullptr;

	//入力の初期化
	input = new Input();
	input->Initialize(winApp);



	Logger::Log("HelloDIrectX!\n");

	MSG msg{};

	//SpriteCommon
	SpriteCommon* spriteCommon = nullptr;

	//初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxcCommon);

	//ObjectCommon
	Object3dCommon* objectCommon=nullptr;
	objectCommon = new Object3dCommon;
	objectCommon->Initialize(dxcCommon);


	TextureManager::GetInstance()->Initialize(dxcCommon);
	//Textureを読んで転送する
	TextureManager::GetInstance()->LoadTexture("resources/uvChecker.png");
	//TextureManager::GetInstance()->LoadTexture("resources/monsterBall.png");

	//3Dマネージャーの初期化
	ModelManager::GetInstance()->Initialize(dxcCommon);


	//Spriteを作成
	std::vector<Sprite*>sprites;
	for (uint32_t i = 0; i < 5; ++i) {
		Sprite* sprite = new Sprite();
		sprite->Initialize(spriteCommon, "resources/uvChecker.png");
		sprite->SetPosition({ 100.0f * i,0.0f });
		sprite->SetSize({ 50.0f,50.0f });
		sprites.push_back(sprite);
	}

	//


	//Modelを生成
	/*モデルコモン*/
	ModelCommon* modelCommon = nullptr;
	modelCommon = new ModelCommon();
	modelCommon->Initialize(dxcCommon);
	/*モデル|見た目*/
	Model* model = nullptr;
	model = new Model();
	model->Initialize(modelCommon);
	Object3d* object3d = nullptr;
	/*Object3d|位置*/
	object3d = new Object3d();
	object3d->SetModel(model);
	object3d->Initialize(objectCommon);


	////2枚目のTextureを読んで転送する
	//TextureManager::GetInstance()->LoadTexture(modelData.material.texturFilePath);




	//SRVを作成するDescriptorHeapの場所を決める
	/*D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU = dxcCommon->GetSRVCPUDescriptorHandle(1);
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = dxcCommon->GetSRVGPUDescriptorHandle(1);*/
	////先頭はImGuiが使っているのでその次を使う
	//textureSrvHandleCPU.ptr += dxcCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//textureSrvHandleGPU.ptr += dxcCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//

	//
	////SRVを作成するDescriptorHeapの場所を決める
	//D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU2 = dxcCommon->GetSRVCPUDescriptorHandle(2);
	//D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU2 = dxcCommon->GetSRVGPUDescriptorHandle(2);


	//dxcCommon->GetDevice()->CreateShaderResourceView(textureResource2.Get(), &srvDesc2, textureSrvHandleCPU2);


	

	bool useMonsterBall = true;
	//ウィンドウのボタンが押されるまでループ
	while (msg.message != WM_QUIT) {



		//windowにメッセージが来てたら最優先で処理させる
		if (winApp->ProcessMessage()) {
			break;
		}
		else {

			//入力更新
			input->Update();

			if (input->TriggerKey(DIK_0)) {
				OutputDebugStringA("Hit 0\n");
			}


			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("WIndow");
			/*ImGui::DragFloat3("Color", &materialData->color.x, 0.01f);
			ImGui::SliderAngle("SpherRotate", &transform.rotate.y);
			ImGui::DragFloat3("LightingColor", &directionalLightData->color.x, 0.01f);*/
			//ImGui::DragFloat3("LightingDir", &directionalLightData->direction.x, 0.01f);
			//ImGui::DragFloat("lightinyencity", &directionalLightData->intensity, 0.01f);
			ImGui::Checkbox("useMonsterBall", &useMonsterBall);
			/*ImGui::DragFloat2("UVTranslate", &uvTransformSprite.translate.x, 0.01f, -10.0f, 10.0f);
			ImGui::DragFloat2("UVScale", &uvTransformSprite.scale.x, 0.01f, -10.0f, 10.0f);
			ImGui::SliderAngle("UVRotate", &uvTransformSprite.rotate.z);*/

			// カラーパレットを縮小表示するためのflag
			static bool showColorPicker = false;

			// カラーパレットの縮小表示
			if (!showColorPicker)
			{
				if (ImGui::Button("color palette"))
					showColorPicker = true;
			}

			// カラーパレットの拡大表示
			if (showColorPicker)
			{
				//ImGui::ColorPicker4("Color", (float*)&materialData->color.x, ImGuiColorEditFlags_Float);


			}


			//ゲームの処理

			

			for (size_t i = 0; i < sprites.size(); ++i) {
				Sprite* sprite = sprites[i];

				//Spriteの更新
				sprite->Update();
			}
			object3d->Update();

			ImGui::End();

			//ImGUi内部のコマンドを生成する
			ImGui::Render();

			//描画前処理
			dxcCommon->PreDraw();

			//Spriteの描画準備
			spriteCommon->CommonDrawing();

			//Modelの描画前準備
			objectCommon->CommonDrawing();
			


			

			//Sprite描画！(DrawCall/ドローコール)。3頂点出一つのインスタンス。インスタンスについては今後
			for (Sprite* sprite : sprites) {

				sprite->Draw();
			}
			object3d->Draw();
			//
			ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dxcCommon->GetCommandList());

			dxcCommon->PostDraw();





			//ゲーム処理

		}
	}
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	OutputDebugStringA("HelloDirectX!\n");

	//解放処理
	//CloseHandle(fenceEvent);

	TextureManager::GetInstance()->Finalize();
	ModelManager::GetInstance()->Finalize();
	//入力解放
	delete input;
	delete dxcCommon;
	delete spriteCommon;
	delete objectCommon;
	delete modelCommon;
	delete model;
	delete object3d;
	for (Sprite* sprite : sprites) {
		delete sprite;
	}
	//CloseWindow
	winApp->Finalize();

	delete winApp;



	return 0;
}