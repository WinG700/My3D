#include "UWorld.h"

UWorld::UWorld()
{
	
}

UWorld::UWorld(Camera* In_Cam)
{
	Cam = In_Cam;
}

void UWorld::Tick(double DeltaSecond)
{
	rasterization->DrawBackground();
	Matrix4x4 Cam_Trans = Cam->ActorTransform.ToAffineMatrix(true);
	//Cam->ActorTransform.Quat.CoutThis("cam quat");
	for (Actor* A : Actors)
	{
		Matrix4x4 A_Trans = A->ActorTransform.ToAffineMatrix();
		A->Tick(DeltaSecond);
		for (UTriangle* Triangle : A->Triangles)
		{	
			//cout << (A_Trans * Triangle->NormalVector) * Cam->ActorTransform.Quat.GetForward() << endl;
			if ((A_Trans * Triangle->NormalVector) * Cam->ActorTransform.Quat.GetForward() < 0)
			{	
				
				//Vector3 x = Cam->ActorTransform.Quat.GetForward();
				//x.CoutThis();
				//Cam->ActorTransform.Quat.GetForward().CoutThis();
				//cout << Triangle->NormalVector * Cam->ActorTransform.Quat.GetForward() << endl;
				Vector3 NewPoint1 = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point1);
				//NewPoint1.CoutThis();
				Vector3 NewPoint2 = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point2);
				//NewPoint2.CoutThis();
				Vector3 NewPoint3 = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point3);
				//NewPoint3.CoutThis();
				//左手坐标系在透视矩阵变换后会上下左右颠倒
				NewPoint1.x = -1.f * NewPoint1.x;
				NewPoint1.y = -1.f * NewPoint1.y;
				NewPoint2.x = -1.f * NewPoint2.x;
				NewPoint2.y = -1.f * NewPoint2.y;
				NewPoint3.x = -1.f * NewPoint3.x;
				NewPoint3.y = -1.f * NewPoint3.y;
				if (NewPoint1.z >= 1.f || NewPoint2.z >= 1.f || NewPoint3.z >= 1.f)
				{
					NewPoint1.CoutThis("1");
					NewPoint2.CoutThis("2");
					NewPoint3.CoutThis("3");
				}

				rasterization->AddTringle(NewPoint1, NewPoint2, NewPoint3, Triangle->color3, false);
			}
			
			//k = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point2);
			//k = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point3);
		}
	}
}

UWorld::~UWorld()
{
}

