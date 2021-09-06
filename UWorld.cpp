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
	for (Actor* A : Actors)
	{
		Matrix4x4 A_Trans = A->ActorTransform.ToAffineMatrix();
		A->Tick(DeltaSecond);
		for (UTriangle* Triangle : A->Triangles)
		{	
			if ((A_Trans * Triangle->NormalVector) * Cam->ActorTransform.Quat.GetForward() < 0)
			{	
				
				Vector3 x = Cam->ActorTransform.Quat.GetForward();
				//x.CoutThis();
				//Cam->ActorTransform.Quat.GetForward().CoutThis();
				//cout << Triangle->NormalVector * Cam->ActorTransform.Quat.GetForward() << endl;
				Vector3 NewPoint1 = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point1);
				//NewPoint1.CoutThis();
				Vector3 NewPoint2 = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point2);
				//NewPoint2.CoutThis();
				Vector3 NewPoint3 = (*Cam->GetPerspectiveMatrix()) * Cam->WorldToCamera(Cam_Trans * A_Trans * Triangle->Point3);
				//NewPoint3.CoutThis();
				
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

