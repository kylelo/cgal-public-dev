#ifndef CGAL_DATA_CLASSIFICATION_SEGMENTATION_ATTRIBUTE_HORIZONTALITY_H
#define CGAL_DATA_CLASSIFICATION_SEGMENTATION_ATTRIBUTE_HORIZONTALITY_H

#include <vector>

#include <CGAL/Point_set_classification.h>

namespace CGAL {

  /*!
    \ingroup PkgDataClassification

    \brief Segmentation attribute based on local horizontality.

    The orientation of the best fitting plane of a local neighborhood
    of the considered point can be useful to disciminate facades from
    the ground.

    \tparam Kernel The geometric kernel used.

  */
template <typename Kernel>
class Segmentation_attribute_horizontality : public Segmentation_attribute
{
  typedef Point_set_classification<Kernel> PSC;

  std::vector<double> horizontality_attribute;
  
public:
  /// \cond SKIP_IN_MANUAL
  double weight;
  double mean;
  double max;
  /// \endcond
  
  /*!
    \brief Constructs the attribute.

    \param M The point set classification object
    \param weight The relative weight of this attribute
    \param on_groups Select if the attribute is computed point-wise of group-wise
  */
  Segmentation_attribute_horizontality (Point_set_classification<Kernel>& M, double weight,
                                        bool on_groups = false) : weight (weight)
  {
    typename Kernel::Vector_3 vertical (0., 0., 1.);

    if (on_groups)
      {
        std::vector<double> values;
        
        values.reserve (M.groups.size());
        for (std::size_t i = 0; i < M.groups.size(); ++ i)
          {
            typename Kernel::Vector_3 normal = M.groups[i].orthogonal_vector();
            normal = normal / std::sqrt (normal * normal);
            values.push_back (1. - std::fabs(normal * vertical));
          }
        for (std::size_t i = 0; i < M.HPS.size(); ++ i)
          if (M.HPS[i].group == (std::size_t)(-1))
            horizontality_attribute.push_back (0.5);
          else
            horizontality_attribute.push_back (values[M.HPS[i].group]);
      }
    else
      {
        for(int i=0; i<(int)M.HPS.size(); i++)
          {
            typename Kernel::Vector_3 normal = M.planes[i].orthogonal_vector();
            normal = normal / std::sqrt (normal * normal);
            horizontality_attribute.push_back (1. - std::fabs(normal * vertical));
          }
      }
    
    this->compute_mean_max (horizontality_attribute, mean, max);
    //    max *= 2;
  }
  virtual double value (std::size_t pt_index)
  {
    return std::max (0., std::min (1., horizontality_attribute[pt_index] / weight));
  }

  virtual std::string id() { return "horizontality"; }
};


}

#endif // CGAL_DATA_CLASSIFICATION_SEGMENTATION_ATTRIBUTE_HORIZONTALITY_H
