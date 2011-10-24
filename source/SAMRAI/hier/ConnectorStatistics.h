/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and COPYING.LESSER.
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Statistical characteristics of a Connector.
 *
 ************************************************************************/
#ifndef included_hier_ConnectorStatistics
#define included_hier_ConnectorStatistics

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/Connector.h"

namespace SAMRAI {
namespace hier {

/*!
 * @brief A utility for writing out various statistics of Connectors.
 */
class ConnectorStatistics
{

public:

   /*!
    * @brief Constructor.
    *
    * @param[i] connector
    */
   explicit ConnectorStatistics(const Connector &connector);

   /*!
    * @brief Print out local and globally reduced statistics on the
    * Boxes.
    *
    * @param[in,out] os The output stream
    *
    * @param[in] border A string to print at the start of every line
    * in the output.
    */
   void
   printNeighborStats(
      std::ostream& os,
      const std::string& border) const;


private:

   /*!
    * @brief Set up things for the entire class.
    *
    * Only called by StartupShutdownManager.
    */
   static void
   initializeCallback();

   /*!
    * @brief Free static timers.
    *
    * Only called by StartupShutdownManager.
    */
   static void
   finalizeCallback();

   /*!
    * @brief Indices for statistical quantites.
    *
    * Relationships (or edges) are from the perspective of the base
    * boxes, so it is possible for two base boxes to have
    * relationships to the same head box, in which case, we count two
    * relationships.  Neighbors are distinct head boxes, so in the
    * same example, there is only one neighbors even though there are
    * two relationships to that neighbor.
    *
    * The MIN_* and MAX_* quantities refer to the min/max over the
    * local base boxes.  When we compute the global min/max of these
    * quantities, that is exactly what they are: min of min, min of
    * max, max of min and max of max.
    */
   enum { NUMBER_OF_BASE_BOXES,
          NUMBER_OF_BASE_CELLS,

          HAS_ANY_NEIGHBOR_SETS,
          NUMBER_OF_NEIGHBOR_SETS,

          HAS_ANY_RELATIONSHIPS,
          NUMBER_OF_RELATIONSHIPS,
          MIN_NUMBER_OF_RELATIONSHIPS,
          MAX_NUMBER_OF_RELATIONSHIPS,

          NUMBER_OF_NEIGHBORS,
          NUMBER_OF_LOCAL_NEIGHBORS,
          NUMBER_OF_REMOTE_NEIGHBORS,
          NUMBER_OF_REMOTE_NEIGHBOR_OWNERS,

          OVERLAP_SIZE,
          LOCAL_OVERLAP_SIZE,
          REMOTE_OVERLAP_SIZE,

          NUMBER_OF_QUANTITIES };

   /*
    * @brief StatisticalQuantities to compute the min, avg and max for.
    *
    * These quantities will be computed locally on each process and
    * globally reduced.  Not all of these quantities are floating
    * points but all are represented as such.
    */
   struct StatisticalQuantities {
      StatisticalQuantities();
      double d_values[NUMBER_OF_QUANTITIES];
   };

   void computeLocalConnectorStatistics(StatisticalQuantities &sq) const;

   //! @brief Connector to compute statistics for.
   const Connector &d_connector;

   /*!
    * @brief Names of the quantities in StatisticalQuantities.
    */
   static std::string s_quantity_names[NUMBER_OF_QUANTITIES];

   /*!
    * @brief Longest length in s_quantity_names.
    */
   static int s_longest_length;

   static tbox::StartupShutdownManager::Handler
      s_initialize_finalize_handler;


};

}
}

#ifdef SAMRAI_INLINE
// #include "SAMRAI/hier/ConnectorStatistics.I"
#endif

#endif  // included_hier_ConnectorStatistics