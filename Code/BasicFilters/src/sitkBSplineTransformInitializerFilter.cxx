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

#include <memory>

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkNumericTraits.h"
#include "itkNumericTraitsVariableLengthVectorPixel.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkComposeImageFilter.h"

#include "sitkBSplineTransformInitializerFilter.h"
#include "itkBSplineTransform.h"
#include "itkBSplineTransformInitializer.h"

// Additional include files
#include "sitkTransform.h"
// Done with additional include files

namespace itk::simple
{

//-----------------------------------------------------------------------------

//
// Default constructor
//
BSplineTransformInitializerFilter::BSplineTransformInitializerFilter() = default;

const detail::MemberFunctionFactory<BSplineTransformInitializerFilter::MemberFunctionType> &
BSplineTransformInitializerFilter::GetMemberFunctionFactory()
{
  static detail::MemberFunctionFactory<MemberFunctionType> static_factory = [] {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 3>();
    factory.RegisterMemberFunctions<PixelIDTypeList, 2>();
    return factory;
  }();

  return static_factory;
}

//
// Destructor
//
BSplineTransformInitializerFilter::~BSplineTransformInitializerFilter() = default;


//
// ToString
//
std::string
BSplineTransformInitializerFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::BSplineTransformInitializerFilter\n";
  out << "  TransformDomainMeshSize: ";
  this->ToStringHelper(out, this->m_TransformDomainMeshSize);
  out << "  Order:";
  this->ToStringHelper(out, this->m_Order);
  out << std::endl;

  out << ProcessObject::ToString();
  return out.str();
}

//
// Execute
//
BSplineTransform
BSplineTransformInitializerFilter::Execute(const Image & image1)
{
  PixelIDValueEnum type = image1.GetPixelID();
  unsigned int     dimension = image1.GetDimension();

  if (GetMemberFunctionFactory().HasMemberFunction(type, dimension))
  {
    return GetMemberFunctionFactory().GetMemberFunction(type, dimension, this)(image1);
  }

  sitkExceptionMacro("Filter does not support image type: " << GetPixelIDValueAsString(type) << " with dimension "
                                                            << dimension << "."); // Zero tolerance
}


//-----------------------------------------------------------------------------

//
// Custom Casts
//
namespace
{}

//-----------------------------------------------------------------------------

//
// ExecuteInternal
//

template <class TImageType>
BSplineTransform
BSplineTransformInitializerFilter::ExecuteInternal(const Image & inImage1)
{
  const unsigned int D = TImageType::ImageDimension;
  switch (this->m_Order)
  {
    case 0:
      return this->ExecuteInternalWithOrder<D, 0>(inImage1);
    case 1:
      return this->ExecuteInternalWithOrder<D, 1>(inImage1);
    case 2:
      return this->ExecuteInternalWithOrder<D, 2>(inImage1);
    case 3:
      return this->ExecuteInternalWithOrder<D, 3>(inImage1);
    default:
      sitkExceptionMacro("Invalid Order: " << this->m_Order << " only orders 0, 1, 2, and 3 supported!");
  }
}

template <unsigned int NDimension, unsigned int NOrder>
BSplineTransform
BSplineTransformInitializerFilter::ExecuteInternalWithOrder(const Image & inImage1)
{
  // Define the input and output image types
  using InputImageType = itk::ImageBase<NDimension>;

  // Get the pointer to the ITK image contained in image1
  typename InputImageType::ConstPointer image1 = this->CastImageToITK<InputImageType>(inImage1);


  using FilterType =
    itk::BSplineTransformInitializer<itk::BSplineTransform<double, NDimension, NOrder>, InputImageType>;
  // Set up the ITK filter
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetImage(image1);

  BSplineTransform sitkTransform(NDimension, NOrder);

  const typename FilterType::TransformType * itkTx =
    dynamic_cast<const typename FilterType::TransformType *>(sitkTransform.GetITKBase());
  if (!itkTx)
  {
    sitkExceptionMacro("Unexpected error conversion to a BSplineTransform!");
  }
  else
  {
    filter->SetTransform(const_cast<typename FilterType::TransformType *>(itkTx));
  }


  typename FilterType::MeshSizeType itkVecTransformDomainMeshSize =
    sitkSTLVectorToITK<typename FilterType::MeshSizeType>(this->GetTransformDomainMeshSize());
  filter->SetTransformDomainMeshSize(itkVecTransformDomainMeshSize);

  filter->InitializeTransform();

  return sitkTransform;
}

//-----------------------------------------------------------------------------


//
// Function to run the Execute method of this filter
//
BSplineTransform
BSplineTransformInitializer(const Image &                 image1,
                            const std::vector<uint32_t> & transformDomainMeshSize,
                            unsigned int                  order)
{
  BSplineTransformInitializerFilter filter;
  filter.SetTransformDomainMeshSize(transformDomainMeshSize);
  filter.SetOrder(order);
  return filter.Execute(image1);
}


} // namespace itk::simple
