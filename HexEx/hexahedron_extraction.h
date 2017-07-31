#ifndef GEO_EXTR_H
#define GEO_EXTR_H
#include"typedefs.h"
#include<vector>
#include<unordered_map>
#include<limits>
#include<algorithm>
#include"functions.h"
#include"handles.h"
/* If you want to use a viewer, you can use qglviewer. */
#ifdef CGAL_LCC_USE_QT
#include "linear_cell_complex_3_viewer_qt.h"
#endif

Aff_transformation* find_tet_parametrization(LCC_3& lcc, Point p, std::vector<Aff_transformation>& parametrization_matrices){
  for(LCC_3::One_dart_per_cell_range<3>::iterator it = lcc.one_dart_per_cell<3>().begin(), itend = lcc.one_dart_per_cell<3>().end(); it != itend; it++){
    std::vector<Point_3> point;
    for(LCC_3::One_dart_per_incident_cell_range<0,3>::iterator it1 = lcc.one_dart_per_incident_cell<0,3>(it).begin(), it1end = lcc.one_dart_per_incident_cell<0,3>(it).end(); it1 != it1end; it1++){
      point.push_back((lcc.info(it1)).parameters);
    }

    Tetrahedron_3 tet(point[0], point[1], point[2], point[3]);
    if(tet.is_degenerate()) continue;
    if(!tet.has_on_unbounded_side(p)) return &(parametrization_matrices[(lcc.info(it)).cell_no]);
  }
  return nullptr;
}

bool does_intersect(Tetrahedron_3 tet, Point_3 p){/**
* If p does not lie on the unbounded side of the tet, this function checks if a prospective unit volume cube in the positive x, y and z directions, with origin at p, would intersect the given tet. 
* If it lies on the unbounded side, we don't consider the volumes tobe intersecting: so the function returns false. 
*/
/*if(tet.is_degenerate()||tet.has_on_bounded_side(p)){if(DEBUG) std::cout<<"Doesn't intersect"<<std::endl; return false;}
  else if(tet.has_on_unbounded_side(p)){if(DEBUG) std::cout<<"Does intersect"<<std::endl; return true;}
  if(DEBUG) std::cout<<"Boundary point"<<std::endl;
  return(tet.has_on_unbounded_side(p+Vector_3(1,0,0))||tet.has_on_unbounded_side(p+Vector_3(0,1,0))||tet.has_on_unbounded_side(p+Vector_3(0,0,1))||tet.has_on_unbounded_side(p+Vector_3(1,1,0))||tet.has_on_unbounded_side(p+Vector_3(1,0,1))||tet.has_on_unbounded_side(p+Vector_3(0,1,1))||tet.has_on_unbounded_side(p+Vector_3(1,1,1)));*/

  if(tet.is_degenerate()||tet.has_on_unbounded_side(p)){//if(DEBUG) std::cout<<"Doesn't intersect"<<std::endl; 
return false;}
  else// if(tet.has_on_bounded_side(p)){//if(DEBUG) std::cout<<"Does intersect"<<std::endl;
return true;// }
 // if(DEBUG) std::cout<<"Boundary point"<<std::endl;
/*  return(tet.has_on_bounded_side(p+Vector_3(1,0,0))||tet.has_on_bounded_side(p+Vector_3(0,1,0))||tet.has_on_bounded_side(p+Vector_3(0,0,1))||tet.has_on_bounded_side(p+Vector_3(1,1,0))||tet.has_on_bounded_side(p+Vector_3(1,0,1))||tet.has_on_bounded_side(p+Vector_3(0,1,1))||tet.has_on_bounded_side(p+Vector_3(1,1,1)));*/
}

//Comparison for finding points with  minimum and maximum of x, y and z
bool xfn(Point_3 i, Point_3 j){ return (i[0]<j[0]); }
bool yfn(Point_3 i, Point_3 j){ return (i[1]<j[1]); }
bool zfn(Point_3 i, Point_3 j){ return (i[2]<j[2]); }


void extract_hexes(LCC_3& input_tet_mesh, LCC_3& output_mesh, std::vector<Aff_transformation>& parametrization_matrices, std::unordered_map<Point_3, Dart_handle>& hex_handles, std::unordered_map<Point_3, Point_3>& output_points){/**
* This function combnes the steps geometry extraction and topology extraction from the paper HexEx. 
* We iterate through each volume (in parametric space, stored in dart_info) in the input mesh, and find all the prospective vertices with integer coordinates in parametric space. If unit cubes formed by joining adjacent integer coordinates in the parametric space intersects the tetrahedron, we make a hexahedron (in our output mesh) corresponding to the inverse parametrization of the integer vertices of the cube. 
*/
 

//iterating through each tetrahedron
  for(LCC_3::One_dart_per_cell_range<3>::iterator it = (input_tet_mesh.one_dart_per_cell<3>()).begin(), itend = (input_tet_mesh.one_dart_per_cell<3>()).end(); it != itend; it++){

    double minx = std::numeric_limits<double>::max(), miny = std::numeric_limits<double>::max(), minz = std::numeric_limits<double>::max(); 
    double maxx = std::numeric_limits<double>::min(), maxy = std::numeric_limits<double>::min(), maxz = std::numeric_limits<double>::min();
    std::vector<Point_3> params;
   /* Dart_handle temp = it;
    Point_3 param = (input_tet_mesh.info(temp)).parameters; params.push_back(param);
    //if(DEBUG) std::cout<<minx<<" "<<maxx<<std::endl;
//using beta pointers to find the vertices of a tet instead of LCC::One_dart_per_unit_cell_range::one_dart_per_incident_cell() because it took significantly less time to compute this way.
    temp = input_tet_mesh.beta(it,0); 
    param = (input_tet_mesh.info(temp)).parameters; params.push_back(param);
    temp = input_tet_mesh.beta(it, 0, 1, 0);
    param = (input_tet_mesh.info(temp)).parameters; params.push_back(param);
    temp = input_tet_mesh.beta(it, 2, 0, 1, 0);
    param = (input_tet_mesh.info(temp)).parameters; params.push_back(param);*/
int i = 0;
for(LCC_3::One_dart_per_incident_cell_range<0,3>::iterator it1 = input_tet_mesh.one_dart_per_incident_cell<0,3>(it).begin(), it1end = input_tet_mesh.one_dart_per_incident_cell<0,3>(it).end(); it1 != it1end; it1++){
  Point param = (input_tet_mesh.info(it1)).parameters; params.push_back(param); i++;
}
//std::cout<<i<<std::endl;

//making a tetrahedron in the parametrized space
    Tetrahedron_3 tet(params[0], params[1], params[2], params[3]); 
    //bounding box of the tetrahedron to find the minimum and maximum of x, y, z coordinates
    Bbox_3 box = tet.bbox(); 
    minx = round(box.xmin());
    maxx = round(box.xmax());
    miny = round(box.ymin());
    maxy = round(box.ymax());
    minz = round(box.zmin());
    maxz = round(box.zmax());
    //if(DEBUG) std::cout<<minx<<" "<<maxx<<std::endl;
// inverse parametrization of the given tet
    Aff_transformation at_inv = (parametrization_matrices[(input_tet_mesh.info(it)).cell_no]).inverse(); 


/** iterating through the possible integer vertices. 
* If the integer vertex lies outside the tet, nothing happens.
* If the integer vertex lies on the boundary of the tet, and if the corresponding cube along positive x, y and z axis intersect with the tet, a hexahedron using inverse parametrization is created.
* If the integer vertex lies inside the tet, the corresponding cube is sure to intersect with the tet, so a hexahedron using inverse parametrization is created.
*/ if(DEBUG) std::cout<<"before triple nested loop"<<std::endl; 
   for(int i = minx; i<= maxx; i++){
      for(int j = miny; j<=maxy; j++){
        for(int k = minz; k<=maxz; k++){ 
          Point_3 p(i,j,k); if(DEBUG) std::cout<<i<<" "<<j<<" "<<k<<std::endl;
          if(does_intersect(tet, p)){ if(DEBUG) std::cout<<"Yes, intersects!"<<std::endl;
            //output_mesh.create_vertex_attribute(p.transform(at_inv));     

/*
* We create a map between integer grid points and inverse-parametrized points called output_points, to avoid repeated calculations and so that each grid point maps to a unique inverse parametrization (this need not happen due to numerical inefficiencies, leading to overlapping hexes) 
* The paper uses the transition function to find the parametrization matrix of adjacent tet- this could be done too, but we have the parametrization matrix itself readily available in parametrization_matrices- so we use that to know parametrization in other matrices (not necessarily adjacent)
*/          Point p0, param; 
            if(output_points.find(p) == output_points.end()){
              p0 = p.transform(at_inv); param = p;
              output_points.emplace(std::make_pair(p, p0));
            }
            else{
              p0 = output_points[p]; param = p;
            }

            Point p1(param[0]+1, param[1], param[2]); p = p1;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p1 = p.transform(at_inv);
                else p1 = p.transform((*at_new).inverse());
              } 
              else p1 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p1));
            }
            else{
              p1 = output_points[p]; 
            }

            Point p2(param[0]+1, param[1]+1, param[2]); p = p2;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p2 = p.transform(at_inv);
                else p2 = p.transform((*at_new).inverse());
              } 
              else p2 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p2));
            }
            else{
              p2 = output_points[p]; 
            }

            Point p3(param[0], param[1]+1, param[2]); p = p3;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p3 = p.transform(at_inv);
                else p3 = p.transform((*at_new).inverse());
              } 
              else p3 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p3));
            }
            else{
              p3 = output_points[p]; 
            }

            Point p4(param[0], param[1]+1, param[2]+1); p = p4;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p4 = p.transform(at_inv);
                else p4 = p.transform((*at_new).inverse());
              } 
              else p4 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p4));
            }
            else{
              p4 = output_points[p]; 
            }

            Point p5(param[0], param[1], param[2]+1); p = p5;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p5 = p.transform(at_inv);
                else p5 = p.transform((*at_new).inverse());
              } 
              else p5 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p5));
            }
            else{
              p5 = output_points[p]; 
            }

            Point p6(param[0]+1, param[1], param[2]+1); p = p6;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p6 = p.transform(at_inv);
                else p6 = p.transform((*at_new).inverse());
              } 
              else p6 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p6));
            }
            else{
              p6 = output_points[p]; 
            }

            Point p7(param[0]+1, param[1]+1, param[2]+1); p = p7;
            if(output_points.find(p) == output_points.end()){
              if(tet.has_on_unbounded_side(p)){
                Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p, parametrization_matrices);
                if(at_new == nullptr) p7 = p.transform(at_inv);
                else p7 = p.transform((*at_new).inverse());
              } 
              else p7 = p.transform(at_inv);
              output_points.emplace(std::make_pair(p, p7));
            }
            else{
              p7 = output_points[p]; 
            }


     /*       if(tet.has_on_unbounded_side(p1)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p1, parametrization_matrices);
              if(at_new == nullptr) p1 = p1.transform(at_inv);
              else p1 = p1.transform((*at_new).inverse());
            } 
            else p1 = p1.transform(at_inv);

            Point p2(param[0]+1, param[1]+1, param[2]); 
            if(tet.has_on_unbounded_side(p2)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p2, parametrization_matrices);
              if(at_new == nullptr) p2 = p2.transform(at_inv);
              else p2 = p2.transform((*at_new).inverse());
            } 
            else p2 = p2.transform(at_inv);//if(!tet.has_on_unbounded_side(p2)) p2 = p2.transform(at_inv);

            Point p3(param[0], param[1]+1, param[2]); 
            if(tet.has_on_unbounded_side(p3)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p3, parametrization_matrices);
              if(at_new == nullptr) p3 = p3.transform(at_inv);
              else p3 = p3.transform((*at_new).inverse());
            } 
            else p3 = p3.transform(at_inv);

            Point p4(param[0], param[1]+1, param[2]+1); 
            if(tet.has_on_unbounded_side(p4)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p4, parametrization_matrices);
              if(at_new == nullptr) p4 = p4.transform(at_inv);
              else p4 = p4.transform((*at_new).inverse());
            } 
            else p4 = p4.transform(at_inv);

            Point p5(param[0], param[1], param[2]+1);
            if(tet.has_on_unbounded_side(p5)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p5, parametrization_matrices);
              if(at_new == nullptr) p5 = p5.transform(at_inv);
              else p5 = p5.transform((*at_new).inverse());
            } 
            else p5 = p5.transform(at_inv);

            Point p6(param[0]+1, param[1], param[2]+1);
            if(tet.has_on_unbounded_side(p6)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p6, parametrization_matrices);
              if(at_new == nullptr) p6 = p6.transform(at_inv);
              else p6 = p6.transform((*at_new).inverse());
            } 
            else p6 = p6.transform(at_inv);

            Point p7(param[0]+1, param[1]+1, param[2]+1);
            if(tet.has_on_unbounded_side(p7)){
              Aff_transformation *at_new = find_tet_parametrization(input_tet_mesh, p7, parametrization_matrices);
              if(at_new == nullptr) p7 = p7.transform(at_inv);
              else p7 = p7.transform((*at_new).inverse());
            } 
            else p7 = p7.transform(at_inv);
*/


           if(hex_handles.find(p0) == hex_handles.end()){ 
 //Dart_handle dh = output_mesh.make_hexahedron(p0, p1, p2, p3, p4, p5, p6, p7);
Dart_handle dh = output_mesh.make_hexahedron(p0, p3, p2, p1, p6, p5, p4, p7);
hex_handles.emplace(std::make_pair(p0, dh));
if(DEBUG) std::cout<<"made hexahedron"<<std::endl;
}
          
          }
        }
      }
    }
  if(DEBUG) std::cout<<"after triple nested"<<std::endl;
  }

// output.off is used to visualize the output_mesh after this step. So LCC is written to output.off file.
  std::ofstream of;
  of.open("output.off");
  CGAL::write_off(output_mesh, of); 
  of.close();
//display the characteristics of the output LCC.
  std::cout<<"***Output mesh***"<<std::endl; output_mesh.display_characteristics(std::cout); std::cout<<std::endl;


#ifdef CGAL_LCC_USE_VIEWER
  display_lcc(output_mesh);
#endif // CGAL_LCC_USE_VIEWER
} 

#endif
