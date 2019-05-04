/**********************************************************************

Copyright (c) Mr.Bin. All rights reserved.
For more information visit: http://blog.csdn.net/webzhuce

**********************************************************************/
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <iostream>


int main(int argc, char* argv[])
{
	//if (argc < 2)
	//{
	//	std::cout<<argv[0]<<" "<<"VTK-File(*.vtk)"<<std::endl;
	//	return EXIT_FAILURE;
	//}
	//����Structured_Points���͵�vtk�ļ���
	vtkSmartPointer<vtkStructuredPointsReader> reader = 
		vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName("./head.vtk");

	//���ƶ������巨��ȡ��ֵ�档
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = 
		vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(reader->GetOutputPort());
	marchingCubes->SetValue(0,500);

	//�����ɵĵ�ֵ�����ݽ���Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(marchingCubes->GetOutputPort());

	//��Mapper�����������Ⱦ���������ʾ
	//////////////////////////////////////��Ⱦ���沿��////////////////////////////////////
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize( 640, 480 );
	renWin->Render();
	renWin->SetWindowName("vtkPipelineDemo");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renWin);

	interactor->Initialize();
	interactor->Start();
	//////////////////////////////////////////////////////////////////////////////////////////////////

	return EXIT_SUCCESS;
}