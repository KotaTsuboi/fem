#pragma once

#include <memory>
#include <stdio.h>
#include <vector>
#include <map>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>

#include "../axis/axis_2d.hpp"
#include "../element/finite_element_2d.hpp"
#include "../output/element_data.hpp"
#include "../output/node_data.hpp"
#include "../structure/structure_2d.hpp"
#include "../util/iterator.hpp"

using std::string;

class VtuWriter {

  public:
    VtuWriter(Structure2D structure)
        : structure(structure) {
        // printf("Initializing writer.\n");
        grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        // printf("Grid newed.\n");

        np = structure.NumNodes();
        nc = structure.NumElements();
        nd = Structure2D::NumDimension;
        // printf("np = %d, nd = %d\n", np, nd);

        auto points = vtkSmartPointer<vtkPoints>::New();
        // printf("Points newed.\n");

        fem::Iterator<std::shared_ptr<Node>> node_iterator = structure.NodeIterator();

        std::map<int, int> index_map;

        int count = 0;

        while (node_iterator.HasNext()) {
            std::shared_ptr<Node> node = node_iterator.Next();
            points->InsertNextPoint(node->X(), node->Y(), node->Z());
            index_map[node->Index()] = count;
            count++;
        }

        grid->SetPoints(points);
        // printf("Points set.\n");

        auto cells = vtkSmartPointer<vtkCellArray>::New();
        // printf("Cells newed.\n");

        fem::Iterator<std::shared_ptr<FiniteElement2D>> element_iterator = structure.ElementIterator();

        while (element_iterator.HasNext()) {
            std::shared_ptr<FiniteElement2D> element = element_iterator.Next();

            vtkNew<vtkTriangle> triangle;

            int i0 = index_map[element->GetNode(0)->Index()];
            int i1 = index_map[element->GetNode(1)->Index()];
            int i2 = index_map[element->GetNode(2)->Index()];

            triangle->GetPointIds()->SetId(0, i0);
            triangle->GetPointIds()->SetId(1, i1);
            triangle->GetPointIds()->SetId(2, i2);

            cells->InsertNextCell(triangle);
        }

        grid->SetCells(VTK_TRIANGLE, cells);
        // printf("Cells set.\n");
    }

    void SetDisplacements(NodeData displacements) {
        auto points = vtkSmartPointer<vtkPoints>::New();

        fem::Iterator<std::shared_ptr<Node>> node_iterator = structure.NodeIterator();

        while (node_iterator.HasNext()) {
            std::shared_ptr<Node> node = node_iterator.Next();
            double dx = displacements.ValueOf(node, Axis2D::X);
            double dy = displacements.ValueOf(node, Axis2D::Y);
            points->InsertNextPoint(node->X() + dx, node->Y() + dy, node->Z());
        }

        grid->SetPoints(points);
    }

    void SetElementData(ElementData element_data, string name) {
        auto cell_data = vtkSmartPointer<vtkDoubleArray>::New();
        cell_data->SetNumberOfTuples(nc);
        cell_data->SetName(name.c_str());

        fem::Iterator<std::shared_ptr<FiniteElement2D>> element_iterator = structure.ElementIterator();

        int count = 0;

        while (element_iterator.HasNext()) {
            std::shared_ptr<FiniteElement2D> element = element_iterator.Next();
            cell_data->SetComponent(count, 0, element_data.ValueOf(element));
            count++;
        }

        grid->GetCellData()->AddArray(cell_data);
    }

    void setVectorData(std::vector<std::vector<double>> v, string name) {
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

    void setScalarData(std::vector<double> v, string name) {
        auto pointData = vtkSmartPointer<vtkDoubleArray>::New();
        pointData->SetNumberOfTuples(np);
        pointData->SetName(name.c_str());

        for (int i = 0; i < np; i++) {
            pointData->SetComponent(i, 0, v[i]);
        }

        grid->GetPointData()->AddArray(pointData);
    }

    void setScalarData(std::vector<int> v, string name) {
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
    Structure2D structure;
    int np;
    int nd;
    int nc;
};
