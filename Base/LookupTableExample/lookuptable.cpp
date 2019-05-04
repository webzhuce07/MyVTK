#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include <vtkLookupTable.h>
#include "vtkSmartPointer.h"

int main()
{
	int i;
	//����������Ķ�������
	static float x[8][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0, 1, 0 },
	{ 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 } };
	//���嵥Ԫ��ÿ4�����㽨��һ���ı��ε�Ԫ������6����Ԫ
	static vtkIdType pts[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 },
	{ 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 3, 0, 4, 7 } };
	//��������
	vtkSmartPointer<vtkPolyData> cube = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	//�洢����
	for (i = 0; i < 8; i++)
		points->InsertPoint(i, x[i]);
	//�趨��Ԫ
	for (i = 0; i < 6; i++)
		polys->InsertNextCell(4, pts[i]);

	//�洢����ֵ
	vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer<vtkFloatArray>::New();
	//�趨ÿ������ı���ֵ
	for (i = 0; i < 8; i++)
		scalars->InsertTuple1(i,  i*4);
	//�������������
	cube->SetPoints(points);
	//�趨��Ԫ����Ϊ�����
	cube->SetPolys(polys);
	//�趨ÿ������ı���ֵ
	cube->GetPointData()->SetScalars(scalars);
	//������ɫӳ���
	vtkSmartPointer<vtkLookupTable> pColorTable = vtkSmartPointer<vtkLookupTable>::New();
	//������ɫ���е���ɫ
	pColorTable->SetNumberOfColors(256);
	pColorTable->SetHueRange(0.67, 0.0);        //ɫ����Χ�Ӻ�ɫ����ɫ
	pColorTable->Build();
	//����ӳ��
	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputData(cube);
	cubeMapper->SetScalarRange(0, 7);
	cubeMapper->SetLookupTable(pColorTable);
	vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	renderer->AddActor(cubeActor);
	renderer->SetBackground(1, 1, 1);
	renWin->SetSize(500, 500);
	renWin->Render();
	iren->Start();
	return 0;
}