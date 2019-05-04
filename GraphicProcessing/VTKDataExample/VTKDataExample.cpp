#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h" 
#include "vtkProperty.h"
#include "vtkLine.h"
#include "vtkCellArray.h"
#include "vtkPolyData.h"


int main()
{
	//����������
	vtkSmartPointer<vtkPoints>points = vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(1.0, 0.0, 0.0);
	points->InsertNextPoint(0.0, 0.0, 1.0);
	points->InsertNextPoint(0.0, 0.0, 0.0);

	//ÿ���������֮��ֱ𴴽�һ����
	//SetId()�ĵ�һ���������߶εĶ˵�ID���ڶ����������ӵĵĵ��ID
	vtkSmartPointer<vtkLine>line0 = vtkSmartPointer<vtkLine>::New();
	line0->GetPointIds()->SetId(0, 0);
	line0->GetPointIds()->SetId(1, 1);

	vtkSmartPointer<vtkLine>line1 = vtkSmartPointer<vtkLine>::New();
	line1->GetPointIds()->SetId(0, 1);
	line1->GetPointIds()->SetId(1, 2);

	vtkSmartPointer<vtkLine>line2 = vtkSmartPointer<vtkLine>::New();
	line2->GetPointIds()->SetId(0, 2);
	line2->GetPointIds()->SetId(1, 0);

	//������Ԫ���飬���ڴ洢���ϴ������߶�
	vtkSmartPointer<vtkCellArray>lines = vtkSmartPointer<vtkCellArray>::New();
	lines->InsertNextCell(line0);
	lines->InsertNextCell(line1);
	lines->InsertNextCell(line2);

	//������߼������ݼ��У�ǰ�߶������ݼ��ļ��νṹ�����߶������˽ṹ
	//����vtkPolyData���͵����ݣ���һ�����ݼ�
	vtkSmartPointer<vtkPolyData>polydata = vtkSmartPointer<vtkPolyData>::New();

	//�������ĵ����ݼ���vtkPolyData������
	polydata->SetPoints(points);  //�����ݶ�����polydata���ݼ��ļ��νṹ��
	polydata->SetLines(lines);  //�������˽ṹ

    //��ʾ����
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polydata);
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->AddActor(actor);
	ren->SetBackground(1, 1, 1);
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	renWin->SetSize(500, 500);
	renWin->Render();
	iren->Start();
	return EXIT_SUCCESS;
}