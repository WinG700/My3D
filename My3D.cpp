// My3D.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <tchar.h>
#include <math.h>
#include "time.h"
#include "Rasterization.h"
#include "Camera.h"
#include "Windows.h"
#include "UWorld.h"



UWorld* CreateWorld(Camera* Local_cam)
{
	UWorld* LocalWorld = new UWorld(Local_cam);
	return LocalWorld;
}

void BuildWorld(UWorld* world)
{
	Actor* Ground = new Actor(FTransfrom(Vector3(0, 0, 0), Quaternions(0, 0, 0, 1)));
	Ground->AddTringle(Vector3(1000.f, 1000.f, 0), Vector3(-1000.f, 1000.f, 0), Vector3(1000.f, -1000.f, 0));
	//Ground->AddTringle(Vector3(-1000.f, -1000.f, 0), Vector3(1000.f, -1000.f, 0), Vector3(-1000.f, 1000.f, 0));
	world->Actors.insert(Ground);
}

int main()
{
	TCHAR A[] = _T("My3D");
	if (screen_init(screen_w, screen_h, A))
		return -1;
	long fps_time = clock(); //计算帧率
	Rasterization* rasterization = new Rasterization(screen_fb); //创建栅格化器
	Camera* cam = new Camera(FTransfrom(Vector3(0, 0, 1500.f), Quaternions(Vector3(0, 1, 0), 90))); //创建相机
	(Quaternions(Vector3(0, 1, 0), 90)* Quaternions(Vector3(0, 1, 0), 1)).CoutThis("3");
	UWorld* World = CreateWorld(cam); //创建世界
	World->rasterization = rasterization;
	BuildWorld(World);
	cam->SetFovX(90.f);
	cam->CreatePerPerspectiveMatrix(NearPlane, FarPlane);
	World->Tick(0.f);
	while (screen_exit == 0 && screen_keys[VK_ESCAPE] == 0) {
		cam->ActorTransform.Quat = cam->ActorTransform.Quat * Quaternions(Vector3(0, 1, 0), -1);
		World->Tick((double)(clock()-fps_time)/1000.f);
		screen_dispatch();
		screen_update();
		cout << clock()- fps_time << " "; //打印帧率
		fps_time = clock();
	}
}
