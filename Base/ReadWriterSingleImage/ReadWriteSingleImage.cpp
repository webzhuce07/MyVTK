/**********************************************************************

Copyright (c) Mr.Bin. All rights reserved.
For more information visit: http://blog.csdn.net/webzhuce

**********************************************************************/
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkJPEGWriter.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

int main(int argc, char* argv[])
{

	//��ȡPNGͼ��
	vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
	reader->SetFileName("E:/TestData/VTK-logo.png");

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

	//��ʾ��ȡ�ĵ���PNGͼ��
	vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetInteractorStyle(style);

	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("ReadWriteSingleImage");

	//�����JPGͼ��
	vtkSmartPointer<vtkJPEGWriter> writer = vtkSmartPointer<vtkJPEGWriter>::New();
	writer->SetFileName("E:/TestData/VTK-logo.jpg");
	writer->SetInputConnection(reader->GetOutputPort());
	writer->Write();

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}