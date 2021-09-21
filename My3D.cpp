// My3D.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <tchar.h>
#include <math.h>
#include "time.h"
#include "Rasterization.h"
#include "Camera.h"
#include "Windows.h"
#include "UWorld.h"

#define LOCKFPS 60

UWorld* CreateWorld(Camera* Local_cam)
{
	UWorld* LocalWorld = new UWorld(Local_cam);
	return LocalWorld;
}

void BuildWorld(UWorld* world)
{
	//添加一个地面
	double GroudSide = 200.0;
	Actor* Ground = new Actor(FTransfrom(Vector3(0, 0, 0), Quaternions(0, 0, 0, 1)));
	Ground->AddVertex({ Vector3(GroudSide, GroudSide, 0), Vector3(-1.0 * GroudSide, GroudSide, 0), Vector3(-1.0 * GroudSide, -1.0 * GroudSide, 0), Vector3(GroudSide, -1.0 * GroudSide, 0) });
	Ground->AddTringle({ {0, 1, 3},{2, 3, 1} });
	world->Actors.push_back(Ground);
	//Ground->AddTringle(Vector3(1000.f, 1000.f, 0), Vector3(-1000.f, 1000.f, 0), Vector3(1000.f, -1000.f, 0));
	//Ground->AddTringle(Vector3(-1000.f, -1000.f, 0), Vector3(1000.f, -1000.f, 0), Vector3(-1000.f, 1000.f, 0));
	
	//添加一个三棱锥
	Actor* TriangularPrism = new Actor(FTransfrom(Vector3(0, 0, 0), Quaternions(0, 0, 0, 1)));
	TriangularPrism->ActorTransform.Quat = TriangularPrism->ActorTransform.Quat * Quaternions(Vector3(0, 0, 1), -3);
	TriangularPrism->AddVertex({Vector3(100.0/cos(Radian(30.0)), 0, 0), Vector3(-100.0*tan(Radian(30.0)), 100.0, 0),  Vector3(-100.0 * tan(Radian(30.0)), -100.0, 0) , Vector3(0, 0, 150)});
	TriangularPrism->AddTringle({{0, 1, 3},{2, 0, 3}, {1, 2, 3}});
	//添加一个正方体
	//double bianchang = 100.0;
	//Actor* TriangularPrism = new Actor(FTransfrom(Vector3(0, 0, 0), Quaternions(0, 0, 0, 1)));
	//TriangularPrism->AddVertex(
	//Vector3()
	//	
	//
	//)
	//TriangularPrism->AddTringle({ {0, 1, 2}});
	world->Actors.push_back(TriangularPrism);
}

int main()
{
	//std::cout << __cplusplus << std::endl;
	TCHAR A[] = _T("My3D");
	if (screen_init(screen_w, screen_h, A))
		return -1;
	long fps_time = clock(); //计算帧率
	long update_time = clock();
	double LockFPSTime = 1000.0/ LOCKFPS;
	Rasterization* rasterization = new Rasterization(screen_fb); //创建栅格化器
	Camera* cam = new Camera(FTransfrom(Vector3(-300, 0, 150.0), Quaternions(0, 0, 0, 1))); //创建相机
	//Camera* cam = new Camera(FTransfrom(Vector3(0, 0, 1500.0), Quaternions(Vector3(0, 1, 0), 90))); //创建相机
	UWorld* World = CreateWorld(cam); //创建世界
	World->rasterization = rasterization;
	BuildWorld(World);
	cam->SetFovX(90.0);
	cam->CreatePerPerspectiveMatrix(NearPlane, FarPlane);
	cam->screen_keys = screen_keys;
	cam->mouse_x = &mouse_x;
	cam->mouse_y = &mouse_y;
	World->Tick(0.f);
	while (screen_exit == 0 && screen_keys[VK_ESCAPE] == 0) {
		update_time = clock();
		//cam->ActorTransform.Quat = cam->ActorTransform.Quat * Quaternions(Vector3(0, 0, 1), -0.5);
		World->Actors[1]->ActorTransform.Quat = World->Actors[1]->ActorTransform.Quat * Quaternions(Vector3(0, 0, 1), -3);
		World->Tick((double)(clock()-fps_time)/1000.0);
		//if (screen_keys[VK_RBUTTON]) cout << "RRRR" ;
		//if (screen_keys[VK_DOWN]) pos += 0.01f;
		//if (screen_keys[VK_LEFT]) alpha += 0.01f;
		//if (screen_keys[VK_RIGHT]) alpha -= 0.01f;
		screen_dispatch();
		screen_update();
		cout << clock()- update_time << " "; //打印帧率
		fps_time = clock();
		if(clock() - update_time < LockFPSTime)
		Sleep(LockFPSTime - clock() + update_time);
	}
}
