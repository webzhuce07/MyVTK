/**********************************************************************

  Author: ��Bin����
  Purpose: test roi
 
**********************************************************************/
#include <vtkQuadric.h> 
#include <vtkSmartPointer.h>
#include <vtkSampleFunction.h> 
#include <vtkSphere.h> 
#include <vtkTransform.h> 
#include <vtkImplicitBoolean.h>
#include <vtkExtractGeometry.h> 
#include <vtkDataSetMapper.h> 
#include <vtkActor.h>
#include <vtkDataSet.h>
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include <vtkRenderWindowInteractor.h> 
#include <vtkCamera.h>
#include <vtkShrinkFilter.h> 

int main()
{
 //������������������
 vtkSmartPointer<vtkQuadric>pQuadric=vtkQuadric::New();
 //���ö������淽�̵�ϵ��
 pQuadric->SetCoefficients(0.5,1.0,0.2,0,0.1,0,0,0.2,0,0);
 //�Զ���������в���,���ɽṹ���㼯���ݶ���
 vtkSmartPointer<vtkSampleFunction>pSmapleFun=vtkSampleFunction::New();
 pSmapleFun->SetSampleDimensions(50,50,50);
 pSmapleFun->SetImplicitFunction(pQuadric);
 //�������ű任
 vtkSmartPointer<vtkTransform>pTrans1=vtkTransform::New();
 pTrans1->Scale(1,0.5,0.333);
    vtkSmartPointer<vtkTransform>pTrans2=vtkTransform::New();
 pTrans2->Scale(0.25,0.5,1.0);
    //����������Բ��
 vtkSmartPointer<vtkSphere>pSphere1=vtkSphere::New();
 pSphere1->SetRadius(0.25);
 pSphere1->SetTransform(pTrans1);
    vtkSmartPointer<vtkSphere>pSphere2=vtkSphere::New();
    pSphere1->SetRadius(0.25);
 pSphere1->SetTransform(pTrans2);
    //�ϲ�������
 vtkSmartPointer<vtkImplicitBoolean>pUnionSphere=vtkImplicitBoolean::New();
    //������
    pUnionSphere->SetOperationType(0);
    pUnionSphere->AddFunction(pSphere1);
    pUnionSphere->AddFunction(pSphere2);
    //��ȡ���ݼ���λ���������ڲ��ĵ�Ԫ
 vtkSmartPointer<vtkExtractGeometry>pExtracFilter=vtkExtractGeometry::New();
 //���ñ���ȡ���ݵ����ݼ�����
 pExtracFilter->SetInput((vtkDataObject *)pSmapleFun->GetOutput());
 //����������
 pExtracFilter->SetImplicitFunction(pUnionSphere);
    //������Ԫ
 vtkSmartPointer<vtkShrinkFilter>pShrinkFilter=vtkShrinkFilter::New();
 //��������ϵ��
 pShrinkFilter->SetShrinkFactor(0.5);
 pShrinkFilter->SetInput((vtkDataObject *)pExtracFilter->GetOutput());
    //�������ݼ�����ӳ����
 vtkSmartPointer<vtkDataSetMapper>pDataSetMapper=vtkDataSetMapper::New();
 pDataSetMapper->SetInput((vtkDataSet *)pShrinkFilter->GetOutput());
 vtkSmartPointer<vtkActor>pActor=vtkActor::New();
 pActor->SetMapper(pDataSetMapper); 
    //����
    vtkSmartPointer<vtkRenderer>renderer=vtkRenderer::New();
 renderer->GetActiveCamera()->Zoom(1.5);
 vtkSmartPointer<vtkRenderWindow>renWin = vtkRenderWindow::New();
 renWin->AddRenderer(renderer);
 vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkRenderWindowInteractor::New();
 iren->SetRenderWindow(renWin);
 renderer->AddActor(pActor);
 renderer->ResetCamera();
 renderer->SetBackground(1,1,1);
 renWin->SetSize(300,300);
 renWin->Render();
 iren->Start();
 return 0;
}
