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
#ifndef sitkEuler3DTransform_h
#define sitkEuler3DTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk::simple
{

/** \class Euler3DTransform
 * \brief A rigid 3D transform with rotation in radians around a
 * fixed center with translation.
 *
 * \sa itk::Euler3DTransform
 */
class SITKCommon_EXPORT Euler3DTransform : public Transform
{
public:
  using Self = Euler3DTransform;
  using Superclass = Transform;

  ~Euler3DTransform() override;

  // construct identity
  Euler3DTransform();

  explicit Euler3DTransform(const std::vector<double> & fixedCenter,
                            double                      angleX = 0.0,
                            double                      angleY = 0.0,
                            double                      angleZ = 0.0,
                            const std::vector<double> & translation = std::vector<double>(3, 0.0));

  Euler3DTransform(const Euler3DTransform &);

  explicit Euler3DTransform(const Transform &);

  Euler3DTransform &
  operator=(const Euler3DTransform &);

  /** Name of this class */
  std::string
  GetName() const override
  {
    return std::string("Euler3DTransform");
  }

  /** fixed parameter */
  void
  SetCenter(const std::vector<double> & params);
  std::vector<double>
  GetCenter() const;

  double
  GetAngleX() const;
  double
  GetAngleY() const;
  double
  GetAngleZ() const;

  /** parameter */
  void
  SetRotation(double angleX, double angleY, double angleZ);

  std::vector<double>
  GetTranslation() const;
  void
  SetTranslation(const std::vector<double> & translation);

  void
  SetComputeZYX(bool _arg);
  bool
  GetComputeZYX() const;
  void
  ComputeZYXOn()
  {
    return this->SetComputeZYX(true);
  }
  void
  ComputeZYXOff()
  {
    return this->SetComputeZYX(false);
  }


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
  std::function<void(double, double, double)>              m_pfSetRotation;
  std::function<double()>                                  m_pfGetAngleX;
  std::function<double()>                                  m_pfGetAngleY;
  std::function<double()>                                  m_pfGetAngleZ;
  std::function<void(const std::vector<double> &)>         m_pfSetTranslation;
  std::function<std::vector<double>()>                     m_pfGetTranslation;
  std::function<void(bool)>                                m_pfSetComputeZYX;
  std::function<bool()>                                    m_pfGetComputeZYX;
  std::function<std::vector<double>()>                     m_pfGetMatrix;
  std::function<void(const std::vector<double> &, double)> m_pfSetMatrix;
};

} // namespace itk::simple

#endif // sitkEuler3DTransform_h
