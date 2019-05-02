/**********************************************************************

Copyright (c) Mr.Bin. All rights reserved.
For more information visit: http://blog.csdn.net/webzhuce

**********************************************************************/
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkDecimatePro.h>
#include <vtkQuadricDecimation.h>
#include <vtkQuadricClustering.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPolydataReader.h>
#include <vtkCamera.h>

int main(int argc, char * argv[])
{
	vtkNew<vtkPolyDataReader> reader;
	reader->SetFileName("E:/TestData/fran_cut.vtk");
	reader->Update();
	vtkSmartPointer<vtkPolyData> original  =  reader->GetOutput();

	std::cout << "��ȡǰ��" << std::endl << "------------" << std::endl;
	std::cout << "ģ�͵���Ϊ�� " << original->GetNumberOfPoints() << std::endl;
	std::cout << "ģ������Ϊ�� " << original->GetNumberOfPolys() << std::endl;

	vtkNew<vtkDecimatePro> decimate;
	decimate->SetInputData(original);
	decimate->SetTargetReduction(.80); 
	decimate->Update();

	vtkSmartPointer<vtkPolyData> decimated = decimate->GetOutput();
	std::cout << "��ȡ��" << std::endl << "------------" << std::endl;
	std::cout << "ģ�͵���Ϊ��" << decimated->GetNumberOfPoints()<< std::endl;
	std::cout << "ģ������Ϊ��" << decimated->GetNumberOfPolys()<< std::endl;

	vtkNew<vtkPolyDataMapper> origianlMapper;
	origianlMapper->SetInputData(original);

	vtkNew<vtkActor> origianlActor;
	origianlActor->SetMapper(origianlMapper);

	vtkNew<vtkPolyDataMapper> decimatedMapper;
	decimatedMapper->SetInputData(decimated);

	vtkNew<vtkActor> decimatedActor;
	decimatedActor->SetMapper(decimatedMapper);

	double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
	double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

	vtkNew<vtkRenderer> leftRenderer;
	leftRenderer->SetViewport(leftViewport);
	leftRenderer->AddActor(origianlActor);
	leftRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkNew<vtkRenderer> rightRenderer;
	rightRenderer->SetViewport(rightViewport);
	rightRenderer->AddActor(decimatedActor);
	rightRenderer->SetBackground(1.0, 1.0, 1.0);

	leftRenderer->GetActiveCamera()->SetPosition(0, -1, 0);
	leftRenderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	leftRenderer->GetActiveCamera()->SetViewUp(0, 0, 1);
	leftRenderer->GetActiveCamera()->Azimuth(30);
	leftRenderer->GetActiveCamera()->Elevation(30);
	leftRenderer->ResetCamera();
	rightRenderer->SetActiveCamera(leftRenderer->GetActiveCamera());

	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->AddRenderer(leftRenderer);
	renderWindow->AddRenderer(rightRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataDecimation");

	vtkNew<vtkRenderWindowInteractor> interactor;
	interactor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	interactor->Start();

	return EXIT_SUCCESS;
}