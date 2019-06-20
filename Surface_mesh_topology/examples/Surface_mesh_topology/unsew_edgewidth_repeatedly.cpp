#include <CGAL/Linear_cell_complex_for_generalized_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <CGAL/Shortest_noncontractible_cycle.h>
#include <CGAL/IO/Color.h>
#include <CGAL/draw_linear_cell_complex.h>
#include <CGAL/squared_distance_3.h>
#define CGAL_USE_BASIC_VIEWER 1


struct Myitem
{
  template<class LCC>
  struct Dart_wrapper
  {
    typedef CGAL::Cell_attribute_with_point<LCC, CGAL::Color, CGAL::Tag_true> Vertex_attribute;
    typedef CGAL::Cell_attribute_with_point<LCC, CGAL::Color, CGAL::Tag_true> Edge_attribute;
    typedef CGAL::cpp11::tuple<Vertex_attribute, Edge_attribute> Attributes;
  };
};

using Traits = CGAL::Linear_cell_complex_traits<3>;
using LCC_3 = CGAL::Linear_cell_complex_for_generalized_map<2, 3, Traits, Myitem>;
using Dart_handle = LCC_3::Dart_handle;
using Dart_const_handle = LCC_3::Dart_const_handle;
using Dart_container = std::vector<Dart_handle>;

struct Weight_functor {
  Weight_functor(const LCC_3& lcc) : m_lcc(lcc) { }
  using Weight_t = double;
  Weight_t operator()(Dart_const_handle dh) const {
    auto x = m_lcc.point_of_vertex_attribute(m_lcc.vertex_attribute(dh));
    auto y = m_lcc.point_of_vertex_attribute(m_lcc.vertex_attribute(m_lcc.template alpha<0>(dh)));
    return CGAL::sqrt(CGAL::squared_distance(x, y));
  }
private:
  const LCC_3& m_lcc;
};


// using SNC = CGAL::Shortest_noncontractible_cycle<LCC_3>;
using SNC = CGAL::Shortest_noncontractible_cycle<LCC_3, Weight_functor>;

LCC_3 lcc;

struct Draw_functor : public CGAL::DefaultDrawingFunctorLCC {
  Draw_functor() {}
  
  template<typename LCC>
  bool colored_vertex(const LCC& alcc, typename LCC::Dart_const_handle dh) const 
  {return alcc.template info<0>(dh) != CGAL::Color();}
  
  template<typename LCC>
  CGAL::Color vertex_color(const LCC& alcc, typename LCC::Dart_const_handle dh) const
  {return alcc.template info<0>(dh);}

  template<typename LCC>
  bool colored_edge(const LCC& alcc, typename LCC::Dart_const_handle dh) const { return true; }

  template<typename LCC>
  CGAL::Color edge_color(const LCC& alcc, typename LCC::Dart_const_handle dh) const
  {return alcc.template info<1>(dh);}

  template<typename LCC>
  bool colored_face(const LCC& alcc, typename LCC::Dart_const_handle dh) const {return true;}

  template<typename LCC>
  CGAL::Color face_color(const LCC& alcc, typename LCC::Dart_const_handle dh) const
  {return CGAL::Color(211, 211, 211);}

  template<typename LCC>
  bool colored_volume(const LCC& alcc, typename LCC::Dart_const_handle dh) const { return false; }
};

int main(int argc, char* argv[]) {
  std::cout << "Program unsew_edgewidth_repeatedly started.\n";
  std::ifstream inp;
  if (argc == 1) inp = std::ifstream("../../examples/Surface_mesh_topology/data/3torus.off");
  else inp = std::ifstream(argv[1]);
  CGAL::load_off(lcc, inp);
  for (auto it = lcc.darts().begin(), itend = lcc.darts().end(); it != itend; ++it) {
    lcc.set_attribute<1>(it, lcc.create_attribute<1>());
    lcc.set_attribute<0>(it, lcc.create_attribute<0>());
  }
  std::cout << "File loaded. Running the main program...\n";
  Draw_functor df;
  for (int loop = 1; ; ++loop) {
    std::cout << "Finding #" << loop << " edge-width:\n";
    Weight_functor wf(lcc);
    SNC snc(lcc, wf);
    SNC::Path cycle;
    SNC::Distance_type x;
    snc.edge_width(cycle, &x);
    if (cycle.size() == 0) {
      std::cout << "  Cannot find edge-width. Stop.\n";
      break;
    }
    
    LCC_3::size_type is_root = lcc.get_new_mark();
    lcc.mark_cell<0>(cycle[0], is_root);
    for (auto dh = lcc.one_dart_per_cell<0>().begin(), dhend = lcc.one_dart_per_cell<0>().end(); dh != dhend; ++dh)
      if (lcc.is_marked(dh, is_root)) {
        lcc.info<0>(dh) = CGAL::Color(255, 0, 0);
        break;
      }
    lcc.free_mark(is_root);

    LCC_3::size_type m = lcc.get_new_mark();
    for (auto e : cycle) {
      lcc.mark_cell<1>(e, m);
    }
    for (auto dh = lcc.one_dart_per_cell<1>().begin(), dhend = lcc.one_dart_per_cell<1>().end(); dh != dhend; ++dh)
      if (lcc.is_marked(dh, m) && !lcc.is_free<2>(dh)) {
        lcc.unmark_cell<1>(dh, m);
        lcc.info<1>(dh) = CGAL::Color(0, 0, 255);
        lcc.unsew<2>(dh);
      }
    lcc.free_mark(m);
    
    std::cout << "  Number of edges in cycle: " << cycle.size() << std::endl;
    std::cout << "  Cycle length: " << x << std::endl;
    std::cout << "  Root: " << lcc.point_of_vertex_attribute(lcc.vertex_attribute(cycle[0])) << std::endl;
    
  }
  CGAL::draw(lcc, "Hello", false, df);
}
