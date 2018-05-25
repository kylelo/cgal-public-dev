#include <CGAL/approx_decomposition.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>

#include <iostream>
#include <fstream>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;

int main()
{
    // read mesh
    Polyhedron mesh;
    
    std::ifstream input("data/elephant.off");
    
    if (!input || !(input >> mesh))
    {
        std::cout << "Failed to read mesh" << std::endl;
        return EXIT_FAILURE;
    }

    if (mesh.empty() || !CGAL::is_triangle_mesh(mesh))
    {
        std::cout << "Input mesh is invalid" << std::endl;
        return EXIT_FAILURE;
    }

    // create property map for cluster-ids
    typedef std::map<Polyhedron::Facet_const_handle, int> Facet_int_map;
    Facet_int_map facet_map;
    boost::associative_property_map<Facet_int_map> facet_property_map(facet_map);

    // decompose mesh with default parameters
    std::size_t clusters_num = CGAL::convex_decomposition(mesh, facet_property_map);

    // write cluster-ids for each facet
    std::cout << "Number of clusters: " << clusters_num << std::endl;
    for (Polyhedron::Facet_const_iterator it = mesh.facets_begin(); it != mesh.facets_end(); ++it)
    {
        std::cout << facet_property_map[it] << " ";
    }
    std::cout << std::endl;

    // write concavity values for all clusters
    for (std::size_t i = 0; i < clusters_num; ++i)
    {
        std::cout << "#" << i << ": " << CGAL::concavity_value(mesh, facet_property_map, i) << std::endl;
    }

    return EXIT_SUCCESS;
}

