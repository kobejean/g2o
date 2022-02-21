// g2o - General Graph Optimization
// Copyright (C) 2011 H. Strasdat
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef G2O_SBA_EDGEPROJECTXYZ2UVD_H
#define G2O_SBA_EDGEPROJECTXYZ2UVD_H

#include "g2o/core/base_binary_edge.h"
#include "g2o/types/slam3d/vertex_pointxyz.h"
#include "g2o_types_sba_api.h"
#include "parameter_cameraparameters.h"
#include "vertex_se3_expmap.h"

namespace g2o {

class G2O_TYPES_SBA_API EdgeProjectXYZ2UVD
    : public BaseBinaryEdge<3, Vector3, VertexPointXYZ, VertexSE3Expmap> {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

  EdgeProjectXYZ2UVD();
  bool read(std::istream& is);
  bool write(std::ostream& os) const;
  void computeError();
  virtual void linearizeOplus();

 public:
  CameraParameters* _cam;  // TODO make protected member?
};


#ifdef G2O_HAVE_OPENGL
  /**
   * \brief Visualize a 3D pose-pose constraint
   */
  class G2O_TYPES_SBA_API EdgeProjectXYZ2UVDDrawAction: public DrawAction{
  public:
    EdgeProjectXYZ2UVDDrawAction();
    virtual HyperGraphElementAction* operator()(HyperGraph::HyperGraphElement* element, 
            HyperGraphElementAction::Parameters* params_);
  private:
    Eigen::Vector3d getDirectionVector(const CameraParameters* cam, Eigen::Vector2d kpt);
  };
#endif
}  // namespace g2o

#endif