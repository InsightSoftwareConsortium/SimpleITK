/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef sitkVersorTransform_h
#define sitkVersorTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk::simple
{

/** \class VersorTransform
 * \brief A 3D rotation transform with rotation as a versor around a
 * fixed center.
 *
 * \sa itk::VersorTransform
 */
class SITKCommon_EXPORT VersorTransform : public Transform
{
public:
  using Self = VersorTransform;
  using Superclass = Transform;

  ~VersorTransform() override;

  // construct identity
  VersorTransform();

  VersorTransform(const VersorTransform &);

  explicit VersorTransform(const Transform &);

  explicit VersorTransform(const std::vector<double> & versor,
                           const std::vector<double> & fixedCenter = std::vector<double>(3, 0.0));

  VersorTransform(const std::vector<double> & axis,
                  double                      angle,
                  const std::vector<double> & fixedCenter = std::vector<double>(3, 0.0));

  VersorTransform &
  operator=(const VersorTransform &);

  /** Name of this class */
  std::string
  GetName() const override
  {
    return std::string("VersorTransform");
  }

  /** fixed parameter */
  void
  SetCenter(const std::vector<double> & params);
  std::vector<double>
  GetCenter() const;


  /** parameter */
  void
  SetRotation(const std::vector<double> & versor);
  void
  SetRotation(const std::vector<double> & axis, double angle);
  std::vector<double>
  GetVersor() const;

  /** additional methods */
  std::vector<double>
  GetMatrix() const;
  void
  SetMatrix(const std::vector<double> & matrix, double tolerance = 1e-10);

protected:
  void
  SetPimpleTransform(std::unique_ptr<PimpleTransformBase> && pimpleTransform) override;

private:
  void
  InternalInitialization(itk::TransformBase * transform);

  template <typename TransformType>
  void
  InternalInitialization(TransformType * transform);


  std::function<void(const std::vector<double> &)>         m_pfSetCenter;
  std::function<std::vector<double>()>                     m_pfGetCenter;
  std::function<void(const std::vector<double> &)>         m_pfSetRotation1;
  std::function<void(const std::vector<double> &, double)> m_pfSetRotation2;
  std::function<std::vector<double>()>                     m_pfGetVersor;
  std::function<std::vector<double>()>                     m_pfGetMatrix;
  std::function<void(const std::vector<double> &, double)> m_pfSetMatrix;
};
} // namespace itk::simple

#endif // sitkVersorTransform_h
