#ifndef MeasurementDet_MuonDetLayerMeasurements_H
#define MeasurementDet_MuonDetLayerMeasurements_H

/** \class MuonDetLayerMeasurements
 *  The class to access recHits and TrajectoryMeasurements from DetLayer.  
 *
 *  $Date: 2006/07/31 23:17:32 $
 *  $Revision: 1.12 $
 *  \author C. Liu, R. Bellan, N. Amapane
 *
 */

#include "FWCore/Framework/interface/Event.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"

#include <vector>

class DetLayer;
class GeomDet;
class TrajectoryMeasurement;
class MuonTransientTrackingRecHit;


//FIXME: these typedefs MUST GO inside the scope of MuonDetLayerMeasurements
typedef std::vector<TrajectoryMeasurement>          MeasurementContainer;
typedef std::pair<const GeomDet*,TrajectoryStateOnSurface> DetWithState;


class MuonDetLayerMeasurements {
 public:
  typedef TransientTrackingRecHit::RecHitPointer RecHitPointer;
  typedef TransientTrackingRecHit::RecHitContainer RecHitContainer;

  MuonDetLayerMeasurements(bool enableDT = true,
			   bool enableCSC = true,
			   bool enableRPC = true,
			   std::string dtlabel = "dt4DSegments", 
			   std::string csclabel = "cscSegments",
			   std::string rpclabel = "rpcRecHits");

  virtual ~MuonDetLayerMeasurements();
  
  /// returns TMeasurements in a DetLayer compatible with the TSOS.
  MeasurementContainer
    measurements( const DetLayer* layer,
		  const TrajectoryStateOnSurface& startingState,
		  const Propagator& prop,
		  const MeasurementEstimator& est,
		  const edm::Event& iEvent) const;

  /// faster version in case the TrajectoryState on the surface of the GeomDet is already available
  MeasurementContainer
    fastMeasurements( const DetLayer* layer,
		      const TrajectoryStateOnSurface& theStateOnDet,
		      const TrajectoryStateOnSurface& startingState,
		      const Propagator& prop,
		      const MeasurementEstimator& est,
		      const edm::Event& iEvent) const;

  /// returns TMeasurements in a DetLayer compatible with the TSOS.
  MeasurementContainer
    measurements( const DetLayer* layer,
		  const TrajectoryStateOnSurface& startingState,
		  const Propagator& prop,
		  const MeasurementEstimator& est) const;

  /// faster version in case the TrajectoryState on the surface of the GeomDet is already available
  MeasurementContainer
    fastMeasurements( const DetLayer* layer,
		      const TrajectoryStateOnSurface& theStateOnDet,
		      const TrajectoryStateOnSurface& startingState,
		      const Propagator& prop,
		      const MeasurementEstimator& est) const;

 
  void setEvent(const edm::Event &);  

  /// returns the rechits which are onto the layer
  RecHitContainer recHits(const DetLayer* layer, const edm::Event& iEvent) const;

  /// returns the rechits which are onto the layer
  RecHitContainer recHits(const DetLayer* layer) const;


 private:

  /// obtain TrackingRecHits from a DetLayer
  RecHitContainer recHits(const GeomDet*, const edm::Event& iEvent) const;


  bool enableDTMeasurement;
  bool enableCSCMeasurement;
  bool enableRPCMeasurement;

  std::string theDTRecHitLabel;
  std::string theCSCRecHitLabel;
  std::string theRPCRecHitLabel;

  bool theEventFlag;
  const edm::Event* theEvent;   
};
#endif

