#pragma once

#include <stdio.h>
#include <vector>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>

using namespace std;

class VtuWriter {

  public:
    VtuWriter(vector<vector<double>> coordinates) {
        // printf("Initializing writer.\n");
        grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        // printf("Grid newed.\n");

        np = (int)coordinates.size();
        nd = (int)coordinates[0].size();
        // printf("np = %d, nd = %d\n", np, nd);

        auto points = vtkSmartPointer<vtkPoints>::New();
        // printf("Points newed.\n");

        for (int i = 0; i < np; i++) {
            points->InsertNextPoint(coordinates[i][0], coordinates[i][1],
                                    coordinates[i][2]);
        }

        grid->SetPoints(points);
        // printf("Points set.\n");

        auto cells = vtkSmartPointer<vtkCellArray>::New();
        // printf("Cells newed.\n");

        for (int i = 0; i < np; i++) {
            vtkIdType id[] = {i};
            cells->InsertNextCell(VTK_VERTEX, id);
        }

        grid->SetCells(VTK_VERTEX, cells);
        // printf("Cells set.\n");
    }

    void setVectorData(vector<vector<double>> v, string name) {
        auto pointData = vtkSmartPointer<vtkDoubleArray>::New();
        pointData->SetNumberOfComponents(nd);
        pointData->SetNumberOfTuples(np);
        pointData->SetName(name.c_str());

        for (int i = 0; i < np; i++) {
            for (int d = 0; d < nd; d++) {
                pointData->SetComponent(i, d, v[i][d]);
            }
        }

        grid->GetPointData()->AddArray(pointData);
    }

    void setScalarData(vector<double> v, string name) {
        auto pointData = vtkSmartPointer<vtkDoubleArray>::New();
        pointData->SetNumberOfTuples(np);
        pointData->SetName(name.c_str());

        for (int i = 0; i < np; i++) {
            pointData->SetComponent(i, 0, v[i]);
        }

        grid->GetPointData()->AddArray(pointData);
    }

    void setScalarData(vector<int> v, string name) {
        auto pointData = vtkSmartPointer<vtkDoubleArray>::New();
        pointData->SetNumberOfTuples(np);
        pointData->SetName(name.c_str());

        for (int i = 0; i < np; i++) {
            pointData->SetComponent(i, 0, v[i]);
        }

        grid->GetPointData()->AddArray(pointData);
    }

    void write(string fileName, bool is_ascii) {
        auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
        writer->SetFileName(fileName.c_str());
        writer->SetInputData(grid);
        if (is_ascii) {
            writer->SetDataModeToAscii();
        }
        writer->Write();
    }

  private:
    vtkSmartPointer<vtkUnstructuredGrid> grid;
    int np;
    int nd;
};
